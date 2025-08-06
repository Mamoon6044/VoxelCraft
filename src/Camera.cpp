#include "Camera.h"

Camera::Camera(GLFWwindow* window, Player& player, std::unordered_map<std::pair<int,int>,
    Chunk, pair_hash>& chunks, DisplayManager& display, GUITexture& hotbar_selection)
    :player(player), head(player.getHead()), body(player.getBody()), chunks(chunks), chunk(chunks.at({0,0})), display(display), hotbar_selection(hotbar_selection) {
    
    this->window = window;
    this->speed = 5.5;
    this->gravity = -0.8;

    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double dx = mouseX - lastMouseX;
    double dy = lastMouseY - mouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void Camera::move() {

    //std::cout<<body.getPosition().x<<","<<body.getPosition().y<<","<<body.getPosition().z<<std::endl;

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {

        float yawRad = (float) glm::radians(yaw);

        float forwardX = (float) glm::sin(yawRad);
        float forwardZ = (float) -glm::cos(yawRad);

        motion(body.getPosition().x - 3*forwardX, body.getPosition().y + 2.25, body.getPosition().z - 3*forwardZ);

    } else if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS){
        float yawRad = (float) glm::radians(yaw);
 
        float forwardX = (float) glm::sin(yawRad);
        float forwardZ = (float) -glm::cos(yawRad);
        float rightX = (float) glm::sin(yawRad + glm::half_pi<float>());
        float rightZ = (float) -glm::cos(yawRad + glm::half_pi<float>());

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.x += forwardX*speed*display.getFrameTime();
            position.z += forwardZ*speed*display.getFrameTime();
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.x -= forwardX*speed*display.getFrameTime();
            position.z -= forwardZ*speed*display.getFrameTime();
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position.x += rightX*speed*display.getFrameTime();
            position.z += rightZ*speed*display.getFrameTime();
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position.x -= rightX*speed*display.getFrameTime();
            position.z -= rightZ*speed*display.getFrameTime();
        }
        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            position.y += speed*display.getFrameTime();
        }
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            position.y -= speed*display.getFrameTime();
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        double dx = mouseX - lastMouseX;
        double dy = lastMouseY - mouseY;

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        yaw += dx * sensitivity;
        pitch -= dy * sensitivity;

        if (pitch > 90) {
            pitch = 90;
        }
        if (pitch < -90) {
            pitch = -90;
        }
    } else {

        float yawRad = (float) glm::radians(yaw);

        float forwardX = (float) glm::sin(yawRad);
        float forwardZ = (float) -glm::cos(yawRad);
        
        motion(body.getPosition().x + 0.35*forwardX, body.getPosition().y + 1.75, body.getPosition().z + 0.35*forwardZ);
    }
}

void Camera::motion(float cameraPosX, float cameraPosY, float cameraPosZ) {

    position.x = cameraPosX;
    position.y = cameraPosY;
    position.z = cameraPosZ;

    if (currentVertSpeed < 0 && currentVertSpeed >= gravity*display.getFrameTime()) {
        initial_height = static_cast<int>(std::floor(body.getPosition().y)+1);
        //std::cout<<"i"<<initial_height<<std::endl;
    }

    if (currentVertSpeed >= -35 * display.getFrameTime()) {
        currentVertSpeed += gravity*display.getFrameTime();
    }
    float yawRad = (float) glm::radians(yaw);
 
    float forwardX = (float) glm::sin(yawRad);
    float forwardZ = (float) -glm::cos(yawRad);
    float rightX = (float) glm::sin(yawRad + glm::half_pi<float>());
    float rightZ = (float) -glm::cos(yawRad + glm::half_pi<float>());

    body.increasePosition(0, currentVertSpeed, 0);
    head.increasePosition(0, currentVertSpeed, 0);
    if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y-0.1),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR) {

        currentVertSpeed = 0;
        isInAir = false;
        body.setPosition(body.getPosition().x, std::floor(body.getPosition().y-0.1)+1.1, body.getPosition().z);
        head.setPosition(body.getPosition().x, std::floor(head.getPosition().y-0.1)+1.1, body.getPosition().z);

        final_height = static_cast<int>(std::floor(body.getPosition().y));

        if(initial_height-final_height > 3) {
            //std::cout<<"f"<<final_height<<std::endl;
            int fall_damage = (initial_height-final_height)-3;
            int after_health = player.getHealth()-fall_damage;
            if(after_health <0){
                fall_damage += after_health;
            }
            player.changeHealth(-fall_damage);
            //std::cout<<player.getHealth()<<std::endl;
            player.changeHearts();
            if(after_health <= 0){
                player.dead();
            }
            initial_height = 0;
            final_height = 0;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

        if(!isInAir) {
            currentVertSpeed = 22*display.getFrameTime();
            isInAir = true;
        }
    }
    bool currentLeft = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    if(currentLeft == false){
        lastLeft = false;
    }
    bool currentRight = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    if(currentRight == false){
        lastRight = false;
    }
    if(currentLeft && !lastLeft){
        if(hotbar_selection.getPosition().x >= -0.375 && hotbar_selection.getPosition().x <= -0.365){
            hotbar_selection.changePosX(0.74);
            slot = 8;
        }else{
            hotbar_selection.changePosX(-0.0925);
            slot--;
        }
        lastLeft = currentLeft;
    }
    if(currentRight && !lastRight){
        if(hotbar_selection.getPosition().x <= 0.375 && hotbar_selection.getPosition().x >= 0.365){
            hotbar_selection.changePosX(-0.74);
            slot = 0;
        }else{
            hotbar_selection.changePosX(0.0925);
            slot++;
        }
        lastRight = currentRight;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        
        double X = forwardX*speed*display.getFrameTime();
        double Z = forwardZ*speed*display.getFrameTime();

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x + 0.4*normalize(forwardX)))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x + 0.4*normalize(forwardX)))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR) {
            X = 0;
            body.setPosition(std::floor(body.getPosition().x +0.4*normalize(forwardX))-normalizepos(forwardX) + 0.6*normalize(forwardX),
              body.getPosition().y, body.getPosition().z);
            head.setPosition(std::floor(head.getPosition().x +0.4*normalize(forwardX))-normalizepos(forwardX) + 0.6*normalize(forwardX),
              head.getPosition().y, head.getPosition().z);
        }

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z + 0.4*normalize(forwardZ)))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z + 0.4*normalize(forwardZ)))%16)) != BlockTypeId::AIR) {
            Z = 0;
            body.setPosition(body.getPosition().x, body.getPosition().y, 
              std::floor(body.getPosition().z +0.4*normalize(forwardZ))-normalizepos(forwardZ) + 0.6*normalize(forwardZ));
            head.setPosition(head.getPosition().x, head.getPosition().y, 
              std::floor(head.getPosition().z +0.4*normalize(forwardZ))-normalizepos(forwardZ) + 0.6*normalize(forwardZ));
        }
        body.setRotY(head.getRotY());
        body.increasePosition(X, 0, Z);
        head.increasePosition(X, 0, Z);

    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

        double X = -forwardX*speed*display.getFrameTime();
        double Z = -forwardZ*speed*display.getFrameTime();

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x - 0.4*normalize(forwardX)))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x - 0.4*normalize(forwardX)))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR) {
            X = 0;
            body.setPosition(std::floor(body.getPosition().x -0.4*normalize(forwardX))-normalizepos(-forwardX) + 0.6*normalize(-forwardX),
              body.getPosition().y, body.getPosition().z);
            head.setPosition(std::floor(head.getPosition().x -0.4*normalize(forwardX))-normalizepos(-forwardX) + 0.6*normalize(-forwardX),
              head.getPosition().y, head.getPosition().z);
        }

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z - 0.4*normalize(forwardZ)))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z - 0.4*normalize(forwardZ)))%16)) != BlockTypeId::AIR) {
            Z = 0;
            body.setPosition(body.getPosition().x, body.getPosition().y, 
              std::floor(body.getPosition().z -0.4*normalize(forwardZ))-normalizepos(-forwardZ) + 0.6*normalize(-forwardZ));
            head.setPosition(head.getPosition().x, head.getPosition().y, 
              std::floor(head.getPosition().z -0.4*normalize(forwardZ))-normalizepos(-forwardZ) + 0.6*normalize(-forwardZ));
        }
        body.setRotY(head.getRotY());
        body.increasePosition(X, 0, Z);
        head.increasePosition(X, 0, Z);

    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){

        double X = rightX*speed*display.getFrameTime();
        double Z = rightZ*speed*display.getFrameTime();

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x + 0.5*normalize(rightX)))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x + 0.5*normalize(rightX)))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR) {
            X = 0;
            body.setPosition(std::floor(body.getPosition().x +0.5*normalize(rightX))-normalizepos(rightX) + 0.5*normalize(rightX),
              body.getPosition().y, body.getPosition().z);
            head.setPosition(std::floor(head.getPosition().x +0.5*normalize(rightX))-normalizepos(rightX) + 0.5*normalize(rightX),
              head.getPosition().y, head.getPosition().z);
        }

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z + 0.5*normalize(rightZ)))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z + 0.5*normalize(rightZ)))%16)) != BlockTypeId::AIR) {
            Z = 0;
            body.setPosition(body.getPosition().x, body.getPosition().y, 
              std::floor(body.getPosition().z +0.5*normalize(rightZ))-normalizepos(rightZ) + 0.5*normalize(rightZ));
            head.setPosition(head.getPosition().x, head.getPosition().y, 
              std::floor(head.getPosition().z +0.5*normalize(rightZ))-normalizepos(rightZ) + 0.5*normalize(rightZ));
        }
        body.setRotY(head.getRotY());
        body.increasePosition(X, 0, Z);
        head.increasePosition(X, 0, Z);

    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){

        double X = -rightX*speed*display.getFrameTime();
        double Z = -rightZ*speed*display.getFrameTime();

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x - 0.5*normalize(rightX)))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x - 0.5*normalize(rightX)))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z))%16)) != BlockTypeId::AIR) {
            X = 0;
            body.setPosition(std::floor(body.getPosition().x -0.5*normalize(rightX))-normalizepos(-rightX) + 0.5*normalize(-rightX),
              body.getPosition().y, body.getPosition().z);
            head.setPosition(std::floor(head.getPosition().x -0.5*normalize(rightX))-normalizepos(-rightX) + 0.5*normalize(-rightX),
              head.getPosition().y, head.getPosition().z);
        }

        if(static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y),
        static_cast<int>(std::floor(body.getPosition().z - 0.5*normalize(rightZ)))%16)) != BlockTypeId::AIR ||
        static_cast<BlockTypeId>(chunk.getBlock(
        static_cast<int>(std::floor(body.getPosition().x))%16,
        std::floor(body.getPosition().y +1),
        static_cast<int>(std::floor(body.getPosition().z - 0.5*normalize(rightZ)))%16)) != BlockTypeId::AIR) {
            Z = 0;
            body.setPosition(body.getPosition().x, body.getPosition().y, 
              std::floor(body.getPosition().z -0.5*normalize(rightZ))-normalizepos(-rightZ) + 0.5*normalize(-rightZ));
            head.setPosition(head.getPosition().x, head.getPosition().y, 
              std::floor(head.getPosition().z -0.5*normalize(rightZ))-normalizepos(-rightZ) + 0.5*normalize(-rightZ));
        }
        body.setRotY(head.getRotY());
        body.increasePosition(X, 0, Z);
        head.increasePosition(X, 0, Z);

    }

    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    double dx = mouseX - lastMouseX;
    double dy = lastMouseY - mouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    if(head.getRotY()-body.getRotY()>=90) {
        head.setRotY(body.getRotY() + 89.95);
    } else if(head.getRotY()-body.getRotY()<=-90) {
        head.setRotY(body.getRotY() - 89.95);
    } else {
        head.increaseRotation(0, -dx*sensitivity, 0);
        yaw = -head.getRotY();
    }

    pitch -= dy * sensitivity;
    //head.increaseRotation(dy * sensitivity, 0, 0);

    if (pitch > 90) {
        pitch = 90;
    }
    if (pitch < -90) {
        pitch = -90;
    }
}

int Camera::normalize(float number){
    if(number<=0){
        return static_cast<int>(std::floor(number));
    }else{
        return static_cast<int>((std::floor(number)+1));
    }
}
int Camera::normalizepos(float number){
    if(number<=0){
        return static_cast<int>(std::floor(number))-1;
    }else{
        return static_cast<int>((std::floor(number)+1));
    }
}

int Camera::getInvSlotNo(){
    return this->slot;
}

void Camera::getChunk() {
    this->chunk = chunks.at({std::floor(body.getPosition().x/16), std::floor(body.getPosition().z/16)});
}

glm::vec3 Camera::getPosition() {
    return position;
}

float Camera::getPitch() {
    return pitch;
}

float Camera::getYaw() {
    return yaw;
}
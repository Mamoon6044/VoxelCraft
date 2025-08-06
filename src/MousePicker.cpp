#include "MousePicker.h"

MousePicker::MousePicker(Camera& camera, GLFWwindow* window, DisplayManager& display, glm::mat4 projection) :camera(camera),display(display){
    this->window = window;
    this->projectionMatrix = projection;
    this->viewMatrix = maths.createViewMatrix(camera);
}

glm::vec3 MousePicker::getCurrentRay(){
    return this->currentRay;
}

void MousePicker::update(){
    this->viewMatrix = maths.createViewMatrix(camera);
    this->currentRay = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay(){
    double mouseX;
    double mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1, 1);
    glm::vec4 eyeCoords = toEyeCoords(clipCoords);
    glm::vec3 worldRay = toWorldCoords(eyeCoords);

    return worldRay;
}
glm::vec2 MousePicker::getNormalizedDeviceCoords(double mouseX, double mouseY){
    float x = (2*mouseX) / display.getWidth() -1;
    float y = (2*mouseY) / display.getHeight() -1;

    return glm::vec2(x,y);
}
glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords){
    if(glm::determinant(projectionMatrix) != 0){
        glm::mat4 invertedProj = glm::inverse(projectionMatrix);
        glm::vec4 eyeCoords = invertedProj * clipCoords;
        //eyeCoords /= eyeCoords.w;
        
        return glm::vec4(eyeCoords.x, eyeCoords.y, -1, 0);
    }else{
        std::cout<<"non-invertible projectionmatrix"<<std::endl;
        return glm::vec4(0);
    }
}
glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords){
    if(glm::determinant(viewMatrix) != 0){
        glm::mat4 invertedView = glm::inverse(viewMatrix);
        glm::vec4 rayWorld = invertedView * eyeCoords;
        //rayWorld /= rayWorld.w;
        
        glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
        mouseRay = glm::normalize(mouseRay);

        return mouseRay;
    }else{
        std::cout<<"non-invertible viewmatrix"<<std::endl;
        return glm::vec3(0);
    }
}
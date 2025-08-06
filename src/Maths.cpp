#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale) {

    glm::mat4 matrix = glm::mat4(1.0f);
    
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::scale(matrix, glm::vec3(scale));
    
    return matrix;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale){

    glm::mat4 matrix = glm::mat4(1.0f);
    
    matrix = glm::translate(matrix, glm::vec3(translation, -0.2));
    matrix = glm::scale(matrix, glm::vec3(scale, 1.0));

    return matrix;
}

glm::mat4 Maths::createViewMatrix(Camera& camera) {

    glm::mat4 viewMatrix = glm::mat4(1.0f);
    
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()),   glm::vec3(0, 1, 0));

    glm::vec3 cameraPos = camera.getPosition();
    glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x,-cameraPos.y,-cameraPos.z);
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);
    
    return viewMatrix;
}
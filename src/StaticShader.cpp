#include "StaticShader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

StaticShader::StaticShader() 
    : ShaderProgram("res/VertexShader.txt", "res/FragmentShader.txt") {
        getAllUniformLocations();
    };


void StaticShader::getAllUniformLocations() {

    location_transformationMatrix = getUniformLocation("transformationMatrix");
    location_projectionMatrix = getUniformLocation("projectionMatrix");
    location_viewMatrix = getUniformLocation("viewMatrix");
    location_lightPosition = getUniformLocation("lightPosition");
    location_lightColour = getUniformLocation("lightColour");
    location_skyColour = getUniformLocation("skyColour");
}

void StaticShader::loadSkyColour(float r, float g, float b) {
    
    ShaderProgram::loadVector(location_skyColour, glm::vec3(r,g,b));
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    
    ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadLight(LightSource light) {
    
    ShaderProgram::loadVector(location_lightPosition, light.getPosition());
    ShaderProgram::loadVector(location_lightColour, light.getColour());
}

void StaticShader::loadViewMatrix(Camera camera) {
    glm::mat4 viewMatrix = maths.createViewMatrix(camera);
    
    ShaderProgram::loadMatrix(location_viewMatrix, viewMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 projection) {

    ShaderProgram::loadMatrix(location_projectionMatrix, projection);
}
#include "GUIShader.h"
#include <iostream>

GUIShader::GUIShader() 
    : ShaderProgram("res/guiVertexShader.txt", "res/guiFragmentShader.txt") {
        getAllUniformLocations();
    };

void GUIShader::getAllUniformLocations() {

    location_transformationMatrix = getUniformLocation("transformationMatrix");
    //std::cout<<location_transformationMatrix<<std::endl;
}

void GUIShader::loadTransformationMatrix(glm::mat4 matrix) {
    
    ShaderProgram::loadMatrix(location_transformationMatrix, matrix);
}
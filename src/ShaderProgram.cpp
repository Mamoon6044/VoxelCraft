#include "ShaderProgram.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>


ShaderProgram::ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile) {

    vertexShaderID = loadShader(GL_VERTEX_SHADER, vertexFile);
    fragmentShaderID = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
}

void ShaderProgram::start(){
    glUseProgram(programID);
}
void ShaderProgram::stop(){
    glUseProgram(0);
}
void ShaderProgram::cleanUp(){
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

int ShaderProgram::getUniformLocation(const char* uniformName) {
    return glGetUniformLocation(programID, uniformName);
}

void ShaderProgram::loadFloat(int location, float value){
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3 vector){
    glUniform3f(location,vector.x,vector.y,vector.z);
}

void ShaderProgram::loadBoolean(int location, bool value){
    float toLoad = 0;
    if(value){
        toLoad = 1;
    }
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(int location, glm::mat4 matrix){
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint ShaderProgram::loadShader(GLenum shaderType, const std::string& filepath) {

    GLuint shaderID = glCreateShader(shaderType);

    const char *ShaderSource = loadShaderSource(filepath);

    glShaderSource(shaderID, 1, &ShaderSource, NULL);
    glCompileShader(shaderID);

    int  success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shaderID;
};

const char* ShaderProgram::loadShaderSource(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return nullptr;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    char* source = new char[content.size() + 1];
    std::memcpy(source, content.c_str(), content.size() + 1); // includes null-terminator

    return source; // Caller must delete[] this
}
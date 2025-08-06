#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {

    protected:
        ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);

        virtual void getAllUniformLocations() = 0;

        const char* loadShaderSource(const std::string& filepath);

        int getUniformLocation(const char* uniformName);

        void loadFloat(int location, float value);

        void loadVector(int location, glm::vec3 vector);

        void loadBoolean(int location, bool value);

        void loadMatrix(int location, glm::mat4 matrix);

    public:
        void start();
        void stop();
        void cleanUp();

    private:
        GLuint loadShader(GLenum shaderType, const std::string& filepath);
        unsigned int programID;
        unsigned int vertexShaderID;
        unsigned int fragmentShaderID;

};
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class Maths {

    public:
        glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
        glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);
        glm::mat4 createViewMatrix(Camera& camera);
};
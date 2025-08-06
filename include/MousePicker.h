#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Maths.h"
#include "DisplayManager.h"

class MousePicker {

    public:
        MousePicker(Camera& camera,GLFWwindow* window, DisplayManager& display, glm::mat4 projection);
        glm::vec3 getCurrentRay();
        void update();
        glm::vec3 calculateMouseRay();

    private:
        glm::vec3 currentRay;
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        GLFWwindow* window;

        Camera& camera;
        DisplayManager& display;
        Maths maths;

        glm::vec2 getNormalizedDeviceCoords(double mouseX, double mouseY);
        glm::vec4 toEyeCoords(glm::vec4 clipCoords);
        glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
};
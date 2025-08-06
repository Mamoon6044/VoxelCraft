#pragma once
#include "StaticShader.h"
#include "Maths.h"
#include "DisplayManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {

    public:

        Renderer(StaticShader& shader);

        void prepare();
        void render(std::unordered_map<TexturedModel*, std::vector<Entity*>>& entities);
        glm::mat4 getProjectionMatrix();

    private:

        const float FOV = 70;
        const float NEAR_PLANE = 0.1;
        const float FAR_PLANE = 500;

        glm::mat4 projectionMatrix;
        Maths maths;
        StaticShader& shader;
        DisplayManager display;

        void prepareTexturedModel(TexturedModel& model);
        void prepareInstance(Entity& entity);
        void unbindTexturedModel();
        void createProjectionMatrix();
};
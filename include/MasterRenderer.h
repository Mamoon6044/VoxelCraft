#pragma once
#include "StaticShader.h"
#include "Renderer.h"
#include "Camera.h"

class MasterRenderer {

    public:

    MasterRenderer(StaticShader& shader);

    void render(Camera& camera);

    void processEntity(Entity& entity);

    glm::mat4 getProjectionMatrix();

    private:

        StaticShader& shader;
        Renderer renderer;

        std::unordered_map<TexturedModel*, std::vector<Entity*>> entities;

};
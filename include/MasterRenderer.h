#pragma once
#include "StaticShader.h"
#include "Renderer.h"
#include "Camera.h"

class MasterRenderer {

    public:

    MasterRenderer(StaticShader& shader);

    void render(Camera& camera);

    void processEntity(Entity& entity);

    private:

        StaticShader& shader;
        Renderer renderer;

        std::unordered_map<TexturedModel*, std::vector<Entity*>> entities;

};
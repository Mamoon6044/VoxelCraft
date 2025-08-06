#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(StaticShader& shader) :shader(shader), renderer(shader) {
}

void MasterRenderer::render(Camera& camera) {

    renderer.prepare();
    shader.start();
    shader.loadViewMatrix(camera);
    //shader.loadLight(light);
    shader.loadSkyColour(0.5f, 0.7f, 1.0f);

    renderer.render(entities);
    shader.stop();
    //entities.clear();
}

glm::mat4 MasterRenderer::getProjectionMatrix(){
    return renderer.getProjectionMatrix();
}

void MasterRenderer::processEntity(Entity& entity) {

    TexturedModel* entityModel = &entity.getModel();
    entities[entityModel].push_back(&entity);
}
#include "Renderer.h"

Renderer::Renderer(StaticShader& shader) :shader(shader){

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    createProjectionMatrix();
    shader.start();
    shader.loadProjectionMatrix(projectionMatrix);
    shader.stop();
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
}

void Renderer::render(std::unordered_map<TexturedModel*, std::vector<Entity*>>& entities) {

    for(const auto& pair : entities) {
        TexturedModel* model = pair.first;
        prepareTexturedModel(*model);
        const std::vector<Entity*>& batch = pair.second;
        for(Entity* entity : batch) {
            prepareInstance(*entity);
            glDrawElements(GL_TRIANGLES, model->getRawModel().getvertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }
}
glm::mat4 Renderer::getProjectionMatrix(){
    return this->projectionMatrix;
}

void Renderer::prepareTexturedModel(TexturedModel& model) {
    RawModel rawModel = model.getRawModel();
    glBindVertexArray(rawModel.getVAOId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getID());
}

void Renderer::prepareInstance(Entity& entity) {
    glm::mat4 transformationMatrix = maths.createTransformationMatrix(entity.getPosition(), entity.getRotX(), entity.getRotY(), entity.getRotZ(), entity.getScale());
    shader.loadTransformationMatrix(transformationMatrix);
}

void Renderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Renderer::createProjectionMatrix() {
    float fov = glm::radians(FOV);
    float aspectRatio = (float) display.getWidth() / (float) display.getHeight();
    projectionMatrix = glm::perspective(fov, aspectRatio, NEAR_PLANE, FAR_PLANE);
}
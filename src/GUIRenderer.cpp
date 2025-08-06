#include "GUIRenderer.h"

GUIRenderer::GUIRenderer(Loader& loader): quad(0,0) {

    std::vector<float> positions = {-1,1,  -1,-1,  1,1,  1,-1};
    this->quad = loader.loadToVAO(positions.data(), positions.size()*sizeof(float));
}

void GUIRenderer::render(std::vector<GUITexture>& GUIs, std::vector<GUITexture>& hearts, std::vector<inventorySlot>& inventory) {

    shader.start();
    glBindVertexArray(quad.getVAOId());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for(GUITexture GUI: GUIs){

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, GUI.getID());
        glm::mat4 transformationMatrix = maths.createTransformationMatrix(GUI.getPosition(), GUI.getScale());
        shader.loadTransformationMatrix(transformationMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getvertexCount());
        //std::cout<<GUI.getPosition().x<<","<<GUI.getPosition().y<<std::endl;
    }
    for(GUITexture heart: hearts){

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, heart.getID());
        glm::mat4 transformationMatrix = maths.createTransformationMatrix(heart.getPosition(), heart.getScale());
        shader.loadTransformationMatrix(transformationMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getvertexCount());
        //std::cout<<GUI.getPosition().x<<","<<GUI.getPosition().y<<std::endl;
    }
    for(inventorySlot slot: inventory){

        GUITexture iso = slot.texture;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, iso.getID());
        glm::mat4 transformationMatrix = maths.createTransformationMatrix(iso.getPosition(), iso.getScale());
        shader.loadTransformationMatrix(transformationMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getvertexCount());
        //std::cout<<GUI.getPosition().x<<","<<GUI.getPosition().y<<std::endl;
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader.stop();
}

void GUIRenderer::cleanUp() {
    shader.cleanUp();
}
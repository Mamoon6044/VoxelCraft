#include "GUITexture.h"

GUITexture::GUITexture(unsigned int textureID, glm::vec2 position, glm::vec2 scale){
    this->position = position;
    this->textureID = textureID;
    this->scale = scale;
}

unsigned int GUITexture::getID(){
    return textureID;
}
glm::vec2 GUITexture::getPosition(){
    return position;
}
glm::vec2 GUITexture::getScale(){
    return scale;
}

void GUITexture::setTextureID(unsigned int newTextureID) {
    this->textureID = newTextureID;
}
void GUITexture::changePosX(float posX){
    position.x += posX;
}
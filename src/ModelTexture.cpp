#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int textureID) {

    this->textureID = textureID;
}

unsigned int ModelTexture::getID() {
    return textureID;
}
void ModelTexture::changeID(unsigned int textureID){
    this->textureID = textureID;
}
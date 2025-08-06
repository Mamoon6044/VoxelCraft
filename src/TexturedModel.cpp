#include "TexturedModel.h"

TexturedModel::TexturedModel(const RawModel& Model, const ModelTexture& texture)
    :rawModel(Model), texture(texture) {

    this->rawModel = Model;
    this->texture = texture;
}

RawModel TexturedModel::getRawModel() {
    return this->rawModel;
}

ModelTexture TexturedModel::getTexture() {
    return this->texture;
}
#include "RawModel.h"

RawModel::RawModel(int VAOId, int vertexCount) {

    this->VAOId = VAOId;
    this->vertexCount = vertexCount;
}

int RawModel::getVAOId() {
    return VAOId;
}

int RawModel::getvertexCount() {
    return vertexCount;
}
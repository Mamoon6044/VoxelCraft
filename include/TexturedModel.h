#pragma once
#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel {

    public:
        TexturedModel(const RawModel& rawModel, const ModelTexture& texture);

        RawModel getRawModel();

        ModelTexture getTexture();

    private:

        RawModel rawModel;

        ModelTexture texture;
};
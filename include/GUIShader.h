#pragma once
#include "ShaderProgram.h"

class GUIShader : public ShaderProgram {

    public:

        GUIShader();
        void loadTransformationMatrix(glm::mat4 matrix);

        void getAllUniformLocations() override;

    private:
        int location_transformationMatrix;
};
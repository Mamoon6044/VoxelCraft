#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Maths.h"
#include "LightSource.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class StaticShader : public ShaderProgram {

    public:

        StaticShader();

        void loadTransformationMatrix(glm::mat4 matrix);
        void loadProjectionMatrix(glm::mat4 projection);
        void loadViewMatrix(Camera camera);
        void loadLight(LightSource light);
        void loadSkyColour(float r, float g, float b);


        void getAllUniformLocations() override;
        
    private:

        int location_transformationMatrix;
        int location_projectionMatrix;
        int location_viewMatrix;
        int location_lightPosition;
        int location_lightColour;
        int location_skyColour;

        Maths maths;
};
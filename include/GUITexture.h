#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GUITexture {

    public:

        GUITexture(unsigned int textureID, glm::vec2 position, glm::vec2 scale);

        unsigned int getID();
        glm::vec2 getPosition();
        glm::vec2 getScale();
        void changePosX(float posX);

        void setTextureID(unsigned int newTextureID);

    private:

        unsigned int textureID;
        glm::vec2 position;
        glm::vec2 scale;
};
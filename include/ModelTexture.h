#pragma once

class ModelTexture {

    public:
        ModelTexture(unsigned int txtureID);

        unsigned int getID();
        void changeID(unsigned int textureID);

    private:
        unsigned int textureID;
};
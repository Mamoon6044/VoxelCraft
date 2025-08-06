#pragma once
#include <glad/glad.h>
#include "RawModel.h"
#include <vector>
#include <string>

class Loader {

    public:
        RawModel loadToVAO(float positions[], size_t sizeP, float texCoords[], size_t sizeT,  float normals[], size_t sizeN, unsigned int indices[], size_t sizeI);
        RawModel loadToVAO(float positions[], size_t sizeP);

        void cleanUp();

        unsigned int loadTexture(const std::string&  fileName);

    private:
        unsigned int createVAO();

        void storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], size_t size);

        void unbindVAO();

        void bindIndicesBuffer(unsigned int indices[], size_t size);

        std::vector<GLuint> vaos;
        std::vector<GLuint> vbos;
        std::vector<GLuint> textures;

};
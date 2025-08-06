#include <glad/glad.h>
#include "Loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>

RawModel Loader::loadToVAO(float positions[], size_t sizeP, float texCoords[], size_t sizeT, float normals[], size_t sizeN, unsigned int indices[], size_t sizeI) {

    int vaoID = createVAO();
    bindIndicesBuffer(indices, sizeI);
    storeDataInAttributeList(0, 3, positions, sizeP);
    storeDataInAttributeList(1, 2, texCoords, sizeT);
    storeDataInAttributeList(2, 3, normals, sizeN);
    unbindVAO();
    return RawModel(vaoID, sizeI/sizeof(unsigned int));
}
RawModel Loader::loadToVAO(float positions[], size_t sizeP) {
    int vaoID = createVAO();
    storeDataInAttributeList(0, 2, positions, sizeP);
    unbindVAO();
    return RawModel(vaoID, (sizeP/sizeof(float))/2);
}

void Loader::cleanUp() {

    for(GLuint vao:vaos){
        glDeleteVertexArrays(1, &vao);
    }
    for(GLuint vbo:vbos){
        glDeleteBuffers(1, &vbo);
    }
    for(GLuint texture:textures){
        glDeleteTextures(1, &texture);
    }
}

GLuint Loader::createVAO() {

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    vaos.push_back(VAO);
    glBindVertexArray(VAO);
    return VAO;
}

unsigned int Loader::loadTexture(const std::string& fileName) {
    int width, height, nrChannels;

    // Flip image vertically (so it's not upside down)
    stbi_set_flip_vertically_on_load(true);

    // Load image data from file
    std::string fullPath = "res/" + fileName + ".png";
    unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 4); // Force 4 channels (RGBA)
    
    if (!data) {
        std::cerr << "Failed to load texture: " << fullPath << std::endl;
        std::exit(-1);
    }

    // Generate OpenGL texture ID
    unsigned int textureID;
    glGenTextures(1, &textureID);

    textures.push_back(textureID);

    // Bind and upload texture data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload image data to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Free CPU-side image data
    stbi_image_free(data);

    return textureID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], size_t size) {

    GLuint VBO;
    glGenBuffers(1, &VBO);
    vbos.push_back(VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attributeNumber);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(unsigned int indices[], size_t size) {

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}
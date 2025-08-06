#pragma once
#include <array>
#include <random>
#include "BlockType.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int CHUNK_SIZE = 16;
constexpr int CHUNK_HEIGHT = 128;

class Chunk {
private:
    std::array<std::array<std::array<uint8_t, CHUNK_SIZE>, CHUNK_HEIGHT>, CHUNK_SIZE> blocks{};
    int chunkX, chunkZ;
    std::mt19937_64 random;

    void generateTerrain();
    void generateTrees();
    void placeTree(int x, int y, int z);
    bool inBounds(int x, int y, int z) const;
    int getTopBlockY(int x, int z) const;

public:
    Chunk(int chunkX, int chunkZ);
    uint8_t getBlock(int x, int y, int z) const;
};
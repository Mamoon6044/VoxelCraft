#include "Chunk.hpp"
#include "PerlinNoise.hpp"
#include <iostream>

Chunk::Chunk(int chunkX, int chunkZ)
    : chunkX(chunkX), chunkZ(chunkZ), random((chunkX * 341873128712ULL) ^ (chunkZ * 132897987541ULL)) {

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                blocks[x][y][z] = static_cast<uint8_t>(BlockTypeId::AIR);
            }
        }
    }

    /*
    blocks[4][11][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][11][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][12][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][12][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[1][11][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[3][11][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][11][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][11][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[3][11][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][11][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[4][11][8] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[2][11][10] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[2][12][10] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[7][11][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][10] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][11] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][11][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][12][10] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][12][11] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][12][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][12][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[8][12][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[9][11][11] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[9][11][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[9][11][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][12] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][11][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][12][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][12][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][12][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][12][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][12][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][13][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][13][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][13][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][13][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[10][13][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][13][1] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][13][2] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][13][3] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][13][4] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][13][5] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[11][11][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][11][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][11][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[11][12][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][12][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][12][7] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[11][11][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][11][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][11][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][11][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[11][12][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[12][12][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][12][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][12][9] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][11][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][11][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][11][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][11][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][12][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][12][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[13][12][13] = static_cast<uint8_t>(BlockTypeId::BEDROCK);
    blocks[14][12][14] = static_cast<uint8_t>(BlockTypeId::BEDROCK);*/

    generateTerrain();
    generateTrees();
    
}

void Chunk::generateTerrain() {
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {

            int worldX = chunkX * CHUNK_SIZE + x;
            int worldZ = chunkZ * CHUNK_SIZE + z;

            int height = 10 + static_cast<int>(glm::sin(worldX * 0.1) * 2 + glm::cos(worldZ * 0.1) * 2);
            //int height = 10 + std::floor(worldZ/3);

            blocks[x][0][z] = static_cast<uint8_t>(BlockTypeId::BEDROCK);

            for (int y = 1; y < height - 2; ++y)
                blocks[x][y][z] = static_cast<uint8_t>(BlockTypeId::STONE);

            blocks[x][height - 2][z] = static_cast<uint8_t>(BlockTypeId::DIRT);
            blocks[x][height - 1][z] = static_cast<uint8_t>(BlockTypeId::DIRT);
            blocks[x][height][z]     = static_cast<uint8_t>(BlockTypeId::GRASS);
        }
    }
}

void Chunk::generateTrees() {
    for (int x = 1; x < CHUNK_SIZE - 1; ++x) {
        for (int z = 1; z < CHUNK_SIZE - 1; ++z) {
            int y = getTopBlockY(x, z);
            if (blocks[x][y][z] == static_cast<uint8_t>(BlockTypeId::GRASS) &&
                std::uniform_real_distribution<float>(0.0f, 1.0f)(random) < 0.008f &&
                inBounds(x + 2, y, z + 2)) {
                placeTree(x, y + 1, z);
            }
        }
    }
}

int Chunk::getTopBlockY(int x, int z) const {
    for (int y = CHUNK_HEIGHT - 1; y >= 0; --y) {
        if (blocks[x][y][z] != static_cast<uint8_t>(BlockTypeId::AIR))
            return y;
    }
    return 0;
}

void Chunk::placeTree(int x, int y, int z) {
    int height = 4 + static_cast<int>(random() % 2);

    for (int i = 0; i < height; ++i) {
        if (y + i < CHUNK_HEIGHT)
            blocks[x][y + i][z] = static_cast<uint8_t>(BlockTypeId::OAK_LOG);
    }

    int index = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = 0; dy <= 2; ++dy) {
            for (int dz = -1; dz <= 1; ++dz) {
                ++index;
                if (index == 7 || index == 9 || index == 25 || index == 27) continue;

                int nx = x + dx;
                int ny = y + height + dy;
                int nz = z + dz;

                if (inBounds(nx, ny, nz))
                    blocks[nx][ny][nz] = static_cast<uint8_t>(BlockTypeId::LEAVES);
            }
        }
    }
}

bool Chunk::inBounds(int x, int y, int z) const {
    return x >= 0 && x < CHUNK_SIZE &&
           y >= 0 && y < CHUNK_HEIGHT &&
           z >= 0 && z < CHUNK_SIZE;
}

uint8_t Chunk::getBlock(int x, int y, int z) const {
    return blocks[x][y][z];
}
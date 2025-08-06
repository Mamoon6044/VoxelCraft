#include "ChunkMeshBuilder.hpp"
#include <iostream>

static constexpr float TEX_SIZE = 1.0f / 8.0f; // Assuming 8x8 texture atlas

static bool isFaceVisible(const Chunk& chunk, int x, int y, int z) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_HEIGHT || z < 0 || z >= CHUNK_SIZE)
        return true;

    auto neighbor = static_cast<BlockTypeId>(chunk.getBlock(x, y, z));
    return neighbor == BlockTypeId::AIR || neighbor == BlockTypeId::LEAVES;
}

static void addFace(std::vector<float>& vertices, std::vector<float>& texCoords, std::vector<float>& normals, std::vector<unsigned int>& indices,
                    int x, int y, int z, FaceDirection face, unsigned int& faceIndex, const BlockType& blockType) {
    
    unsigned int baseIndex = faceIndex * 4;

    float xf = static_cast<float>(x);
    float yf = static_cast<float>(y);
    float zf = static_cast<float>(z);

    switch (face) {
        case FaceDirection::TOP:
            vertices.insert(vertices.end(), {
                xf,     yf + 1, zf,
                xf,     yf + 1, zf + 1,
                xf + 1, yf + 1, zf + 1,
                xf + 1, yf + 1, zf
            });
            break;
        case FaceDirection::BOTTOM:
            vertices.insert(vertices.end(), {
                xf,     yf, zf + 1,
                xf,     yf, zf,
                xf + 1, yf, zf,
                xf + 1, yf, zf + 1
            });
            break;
        case FaceDirection::FRONT:
            vertices.insert(vertices.end(), {
                xf + 1, yf + 1, zf,
                xf + 1, yf,     zf,
                xf,     yf,     zf,
                xf,     yf + 1, zf
            });
            break;
        case FaceDirection::BACK:
            vertices.insert(vertices.end(), {
                xf,     yf + 1, zf + 1,
                xf,     yf,     zf + 1,
                xf + 1, yf,     zf + 1,
                xf + 1, yf + 1, zf + 1
            });
            break;
        case FaceDirection::LEFT:
            vertices.insert(vertices.end(), {
                xf, yf + 1, zf,
                xf, yf,     zf,
                xf, yf,     zf + 1,
                xf, yf + 1, zf + 1,
            });
            break;
        case FaceDirection::RIGHT:
            vertices.insert(vertices.end(), {
                xf + 1, yf + 1, zf + 1,
                xf + 1, yf,     zf + 1,
                xf + 1, yf,     zf,
                xf + 1, yf + 1, zf
            });
            break;
        default:
            break;
    }

    UV uv = blockType.getUV(face);
    float u = uv.u * TEX_SIZE;
    float v = uv.v * TEX_SIZE;

    texCoords.insert(texCoords.end(), {
        u,          v+TEX_SIZE,
        u,          v,
        u+TEX_SIZE, v,
        u+TEX_SIZE, v+TEX_SIZE
    });

    glm::vec3 normal;

    switch (face) {
        case FaceDirection::TOP:    normal = {  0.0f,  1.0f,  0.0f }; break;
        case FaceDirection::BOTTOM: normal = {  0.0f, -1.0f,  0.0f }; break;
        case FaceDirection::FRONT:  normal = {  0.0f,  0.0f, -1.0f }; break;
        case FaceDirection::BACK:   normal = {  0.0f,  0.0f,  1.0f }; break;
        case FaceDirection::LEFT:   normal = { -1.0f,  0.0f,  0.0f }; break;
        case FaceDirection::RIGHT:  normal = {  1.0f,  0.0f,  0.0f }; break;
        default:                    normal = {  0.0f,  0.0f,  0.0f }; break;
    }

    for (int i = 0; i < 4; ++i) {
        normals.insert(normals.end(), {
            normal.x, normal.y, normal.z
        });
    }

    indices.insert(indices.end(), {
        baseIndex, baseIndex+1, baseIndex+2,
        baseIndex, baseIndex+2, baseIndex+3
    });

    ++faceIndex;
}

MeshData ChunkMeshBuilder::generateChunkMesh(Chunk& chunk) {
    std::vector<float> vertices;
    std::vector<float> texCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;

    unsigned int faceIndex = 0;

    for (int x = 0; x < CHUNK_SIZE; ++x) {
        for (int z = 0; z < CHUNK_SIZE; ++z) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                BlockTypeId blockId = static_cast<BlockTypeId>(chunk.getBlock(x, y, z));
                if (blockId == BlockTypeId::AIR) continue;

                const BlockType& block = getBlockType(blockId);

                if (isFaceVisible(chunk, x, y, z - 1)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::FRONT, faceIndex, block);
                if (isFaceVisible(chunk, x, y, z + 1)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::BACK, faceIndex, block);
                if (isFaceVisible(chunk, x - 1, y, z)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::LEFT, faceIndex, block);
                if (isFaceVisible(chunk, x + 1, y, z)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::RIGHT, faceIndex, block);
                if (isFaceVisible(chunk, x, y + 1, z)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::TOP, faceIndex, block);
                if (isFaceVisible(chunk, x, y - 1, z)) addFace(vertices, texCoords, normals, indices, x, y, z, FaceDirection::BOTTOM, faceIndex, block);
            }
        }
    }

    return { vertices, texCoords, normals, indices };
}
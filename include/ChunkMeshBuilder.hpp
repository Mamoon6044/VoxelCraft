#pragma once

#include <vector>
#include "Chunk.hpp"
#include "BlockType.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct MeshData {
    std::vector<float> vertices;
    std::vector<float> texCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;
};

class ChunkMeshBuilder {
public:
    static MeshData generateChunkMesh(Chunk& chunk);
};
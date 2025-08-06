#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "RawModel.h"
#include "Loader.h"

class OBJLoader {
public:
    static RawModel loadObjModel(const std::string& fileName, Loader& loader);

private:
    struct Vertex {
        int posIndex;
        int texIndex;
        int normIndex;

        bool operator==(const Vertex& other) const {
            return posIndex == other.posIndex &&
                   texIndex == other.texIndex &&
                   normIndex == other.normIndex;
        }
    };

    struct VertexHasher {
        std::size_t operator()(const Vertex& v) const {
            return ((std::hash<int>()(v.posIndex) ^
                    (std::hash<int>()(v.texIndex) << 1)) >> 1) ^
                   (std::hash<int>()(v.normIndex) << 1);
        }
    };

    static void processVertex(
        const std::string& token,
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec2>& texCoords0,
        const std::vector<glm::vec3>& normals0,
        std::unordered_map<Vertex, unsigned int, VertexHasher>& uniqueVertexMap,
        unsigned int& nextIndex,
        std::vector<float>& vertices,
        std::vector<float>& texCoords,
        std::vector<float>& normals,
        std::vector<unsigned int>& indices
    );
};
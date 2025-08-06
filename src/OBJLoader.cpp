#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

RawModel OBJLoader::loadObjModel(const std::string& fileName, Loader& loader) {
    std::ifstream file("res/" + fileName + ".obj");

    if (!file.is_open()) {
        std::cerr << "Failed to open file: res/" << fileName << ".obj\n";
        exit(EXIT_FAILURE);
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords0;
    std::vector<glm::vec3> normals0;

    std::vector<float> vertices;
    std::vector<float> texCoords;
    std::vector<float> normals;
    std::vector<unsigned int> indices;

    std::unordered_map<Vertex, unsigned int, VertexHasher> uniqueVertexMap;
    unsigned int nextIndex = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            positions.push_back(glm::vec3(x, y, z));
        } else if (prefix == "vt") {
            float u, v;
            ss >> u >> v;
            texCoords0.push_back(glm::vec2(u, v));
        } else if (prefix == "vn") {
            float nx, ny, nz;
            ss >> nx >> ny >> nz;
            normals0.push_back(glm::vec3(nx, ny, nz));
        } else if (prefix == "f") {
            std::string token;
            std::vector<std::string> faceVertices;

            while (ss >> token) {
                faceVertices.push_back(token);
            }

            // Triangulate face (fan method)
            for (size_t i = 1; i < faceVertices.size() - 1; ++i) {
                processVertex(faceVertices[0], positions, texCoords0, normals0, uniqueVertexMap, nextIndex, vertices, texCoords, normals, indices);
                processVertex(faceVertices[i], positions, texCoords0, normals0, uniqueVertexMap, nextIndex, vertices, texCoords, normals, indices);
                processVertex(faceVertices[i + 1], positions, texCoords0, normals0, uniqueVertexMap, nextIndex, vertices, texCoords, normals, indices);
            }
        }
    }

    file.close();

    return loader.loadToVAO(
        vertices.data(), vertices.size() * sizeof(float),
        texCoords.data(), texCoords.size() * sizeof(float),
        normals.data(), normals.size() * sizeof(float),
        indices.data(), indices.size() * sizeof(unsigned int)
    );
}

void OBJLoader::processVertex(
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
) {
    std::istringstream ss(token);
    std::string vStr, vtStr, vnStr;

    std::getline(ss, vStr, '/');
    std::getline(ss, vtStr, '/');
    std::getline(ss, vnStr, '/');

    int v = std::stoi(vStr) - 1;
    int vt = !vtStr.empty() ? std::stoi(vtStr) - 1 : 0;
    int vn = !vnStr.empty() ? std::stoi(vnStr) - 1 : 0;

    Vertex vertex = { v, vt, vn };

    auto it = uniqueVertexMap.find(vertex);
    if (it != uniqueVertexMap.end()) {
        indices.push_back(it->second);
        return;
    }

    glm::vec3 pos = positions[v];
    vertices.push_back(pos.x);
    vertices.push_back(pos.y);
    vertices.push_back(pos.z);

    glm::vec2 tex = texCoords0[vt];
    texCoords.push_back(tex.x);
    texCoords.push_back(tex.y);

    glm::vec3 norm = normals0[vn];
    normals.push_back(norm.x);
    normals.push_back(norm.y);
    normals.push_back(norm.z);

    uniqueVertexMap[vertex] = nextIndex;
    indices.push_back(nextIndex++);
}
#include "render_engine/obj_loader.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>


RawModel ObjLoader::loadObjModel(std::string const& filename, Loader& loader) {
    std::ifstream fin(filename.c_str());

    if (!fin.is_open()) {
        std::cerr << "[ERROR]: Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    std::vector<GLuint>  _indices;
    std::vector<GLfloat> _positions;
    std::vector<GLfloat> _texCoords;
    std::vector<GLfloat> _normals;

    std::string line;
    int last = 0;

    while (std::getline(fin, line)) {
        std::vector<std::string> tokens = split(line, " ");
        if (tokens.empty()) {
            continue;
        }

        if (tokens[0] == "v") {
            positions.push_back(glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
        }
        else if (tokens[0] == "vt") {
            texCoords.push_back(glm::vec2(stof(tokens[1]), stof(tokens[2])));
        }
        else if (tokens[0] == "vn") {
            normals.push_back(glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
        }
        else if (tokens[0] == "f") {

            fin.seekg(last);
            _positions = std::vector<GLfloat>(3 * positions.size());
            _texCoords = std::vector<GLfloat>(2 * positions.size());
            _normals   = std::vector<GLfloat>(3 * positions.size());
            break;
        }

        last = fin.tellg();
    }

    while (std::getline(fin, line)) {
        std::vector<std::string> face = split(line, " ");
        if (face.empty() || face[0] != "f") {
            continue;
        }

        std::vector<std::string> v1 = split(face[1], "/");
        std::vector<std::string> v2 = split(face[2], "/");
        std::vector<std::string> v3 = split(face[3], "/");

        processVertex(v1, positions, texCoords, normals, _indices, _positions, _texCoords, _normals);
        processVertex(v2, positions, texCoords, normals, _indices, _positions, _texCoords, _normals);
        processVertex(v3, positions, texCoords, normals, _indices, _positions, _texCoords, _normals);
    }

    return loader.loadToVao(_positions, _texCoords, _normals, _indices);
}

void ObjLoader::processVertex(std::vector<std::string> const& vertexData,
                              std::vector<glm::vec3> const& positions,
                              std::vector<glm::vec2> const& texCoords,
                              std::vector<glm::vec3> const& normals,
                              std::vector<GLuint>& _indices,
                              std::vector<GLfloat>& _positions,
                              std::vector<GLfloat>& _texCoords,
                              std::vector<GLfloat>& _normals)
{
    GLuint idx = stoi(vertexData[0]) - 1;
    _indices.push_back(idx);

    glm::vec3 position = positions[stoi(vertexData[0]) - 1];
    _positions[idx * 3] = position.x;
    _positions[idx * 3 + 1] = position.y;
    _positions[idx * 3 + 2] = position.z;

    glm::vec2 texCoord = texCoords[stoi(vertexData[1]) - 1];
    _texCoords[idx * 2] = texCoord.x;
    _texCoords[idx * 2 + 1] = 1 - texCoord.y;

    glm::vec3 normal = normals[stoi(vertexData[2]) - 1];
    _normals[idx * 3] = normal.x;
    _normals[idx * 3 + 1] = normal.y;
    _normals[idx * 3 + 2] = normal.z;
}

std::vector<std::string> ObjLoader::split(std::string const& s, std::string const& delim)
{
    std::vector<std::string> arr;
    char* cs = const_cast<char*>(s.c_str());
    char* token;
    token = strtok(cs, delim.c_str());
    while (token) {
        arr.push_back(token);
        token = strtok(NULL, delim.c_str());
    }
    return arr;
}

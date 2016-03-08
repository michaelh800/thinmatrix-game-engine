#pragma once
#include "models/raw_model.hpp"
#include "render_engine/loader.hpp"
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace ObjLoader {
    RawModel loadObjModel(std::string const& filename, Loader& loader);

    void processVertex(std::vector<std::string> const& vectorData,
                       std::vector<glm::vec3> const& positions,
                       std::vector<glm::vec2> const& texCoords,
                       std::vector<glm::vec3> const& normals,
                       std::vector<GLuint>& _indices,
                       std::vector<GLfloat>& _positions,
                       std::vector<GLfloat>& _texCoords,
                       std::vector<GLfloat>& _normals);

    std::vector<std::string> split(std::string const& s, std::string const& delim);
};

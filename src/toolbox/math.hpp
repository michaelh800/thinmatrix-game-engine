#pragma once
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace Math {

glm::mat4 createTransformationMatrix(
    glm::vec2 const& translation,
    glm::vec2 const& scale);

glm::mat4 createTransformationMatrix(
    glm::vec3 const& translation,
    glm::vec3 const& rotation,
    glm::vec3 const& scale);

float barryCentric(
    glm::vec3 const& p1,
    glm::vec3 const& p2,
    glm::vec3 const& p3,
    glm::vec2 const& pos);
};

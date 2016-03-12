#include "toolbox/math.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


glm::mat4 Math::createTransformationMatrix(glm::vec2 const& translation,
                                           glm::vec2 const& scale)
{
    glm::mat4 matrix = glm::mat4();

    matrix = glm::translate(matrix, glm::vec3(translation, 0.0f));
    matrix = glm::scale    (matrix, glm::vec3(scale, 1.0f));

    return matrix;
}

glm::mat4 Math::createTransformationMatrix(glm::vec3 const& translation,
                                           glm::vec3 const& rotation,
                                           glm::vec3 const& scale)
{
    glm::mat4 matrix = glm::mat4();

    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate   (matrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate   (matrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate   (matrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    matrix = glm::scale    (matrix, scale);

    return matrix;
}

float Math::barryCentric(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3,
    glm::vec2 const& pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

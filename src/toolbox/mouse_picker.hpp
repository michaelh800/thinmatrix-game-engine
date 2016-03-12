#pragma once
#include "entities/camera.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class MousePicker {
public:
    MousePicker(Camera const& cam, glm::mat4 const& projection);

    glm::vec3 const& getCurrentRay() const;

    void update();

private:
    glm::vec3 calculateMouseRay();

    Camera const& camera_;
    glm::mat4 projectionMatrix_;
    glm::mat4 viewMatrix_;
    glm::vec3 currentRay_;
};

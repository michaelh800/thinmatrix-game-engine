#pragma once
#include "terrain/terrain.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    Camera(bool freeRoam=false);

    void update(Terrain const& terrain);
    glm::mat4 getViewMatrix() const;
    glm::vec3 const& getPosition() const;

private:
    bool freeRoam_;

    const glm::vec3 up_     {0, 1,  0};
    glm::vec3 position_     {0, 0,  0};
    glm::vec3 viewDirection_{0, 0, -1};

    void updateDirection(glm::vec2 const& mousePositionDelta);
    void updatePosition(Terrain const& terrain);
};

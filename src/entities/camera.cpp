#include "entities/camera.hpp"
#include "render_engine/display_manager.hpp"
#include <SFML/Window.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>


namespace {
    constexpr float EYE_LEVEL = 6.0f;
    constexpr float WALK_SPEED = 20.0f;
    constexpr float RUN_SPEED = 100.0f;
    constexpr float SENSITIVITY = 0.005f;
}

Camera::Camera(bool freeRoam)
    : freeRoam_(freeRoam)
{
    position_ += glm::vec3(0.0f, EYE_LEVEL, 0.0f);
}

void Camera::update(Terrain const& terrain) {
    sf::Vector2i mousePositionDelta = DisplayManager::getMousePositionDelta();
    updateDirection(glm::vec2(mousePositionDelta.x, mousePositionDelta.y));
    updatePosition(terrain);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position_, position_ + viewDirection_, up_);
}

void Camera::invertPitch() {
    viewDirection_.y *= -1.0f;
}

glm::vec3& Camera::getPosition() {
    return position_;
}

void Camera::updateDirection(glm::vec2 const& mousePositionDelta) {
    if (glm::length(mousePositionDelta) > 100) return;

    glm::vec3 right = glm::cross(viewDirection_, up_);

    glm::mat4 matrix = glm::mat4();
    matrix = glm::rotate(matrix, -mousePositionDelta.x * SENSITIVITY, up_);
    matrix = glm::rotate(matrix, -mousePositionDelta.y * SENSITIVITY, right);

    viewDirection_ = glm::normalize(glm::vec3(matrix * glm::vec4(viewDirection_, 0)));
}

void Camera::updatePosition(Terrain const& terrain) {
    float speed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ? RUN_SPEED : WALK_SPEED;
    float dt = DisplayManager::getFrameTime().asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
       position_ += speed * dt * viewDirection_;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        position_ -= speed * dt * viewDirection_;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        position_ -= speed * dt * glm::cross(viewDirection_, up_);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        position_ += speed * dt * glm::cross(viewDirection_, up_);
    }

    if (!freeRoam_) {
        position_.y = terrain.getHeightOfTerrain(position_.x, position_.z) + EYE_LEVEL;
    }
}

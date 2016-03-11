#include "toolbox/mouse_picker.hpp"
#include "render_engine/display_manager.hpp"


namespace {

glm::vec2 getNormalizeDeviceCoords(float mouseX, float mouseY) {
    sf::Vector2u dimensions = DisplayManager::getWindow().getSize();
    float x = (2.0f * mouseX) / (float)dimensions.x - 1.0f;
    float y = (2.0f * mouseY) / (float)dimensions.y - 1.0f;
    return {x, -y};
}

glm::vec4 toEyeCoords(glm::vec4 const& clipCoords, glm::mat4 const& projection) {
    glm::vec4 eyeCoords = glm::inverse(projection) * clipCoords;
    return {eyeCoords.x, eyeCoords.y, -1.0f, 0.0f};
}

glm::vec3 toWorldCoords(glm::vec4 const& eyeCoords, glm::mat4 const& view) {
    auto mouseRay = glm::vec3(glm::inverse(view) * eyeCoords);
    return glm::normalize(mouseRay);
}

}

MousePicker::MousePicker(Camera const& cam, glm::mat4 const& projection)
    : camera_(cam)
    , projectionMatrix_(projection)
    , viewMatrix_(cam.getViewMatrix())
{ }

glm::vec3 const& MousePicker::getCurrentRay() const {
    return currentRay_;
}

void MousePicker::update() {
    viewMatrix_ = camera_.getViewMatrix();
    currentRay_ = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay() {
    auto mousePos = sf::Mouse::getPosition(DisplayManager::getWindow());
    auto normalizedCoords = getNormalizeDeviceCoords(mousePos.x, mousePos.y);
    auto clipCoords = glm::vec4(normalizedCoords, -1.0f, 1.0f);
    auto eyeCoords = toEyeCoords(clipCoords, projectionMatrix_);
    return toWorldCoords(eyeCoords, viewMatrix_);
}

#include "entities/light.hpp"


Light::Light(glm::vec3 const& position, glm::vec3 const& color, glm::vec3 const& attenuation)
    : position_(position)
    , color_(color)
    , attenuation_(attenuation)
{ }

glm::vec3 const& Light::getPosition() const { return position_; }
void Light::setPosition(glm::vec3 const& position) { position_ = position; }

glm::vec3 const& Light::getColor() const { return color_; }
void Light::setColor(glm::vec3 const& color) { color_ = color; }

glm::vec3 const& Light::getAttenuation() const { return attenuation_; }

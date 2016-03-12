#pragma once
#include <glm/vec3.hpp>

class Light {
public:
    Light(glm::vec3 const& position,
          glm::vec3 const& color,
          glm::vec3 const& attenuation=glm::vec3(1, 0, 0));

    glm::vec3 const& getPosition() const;
    void setPosition(glm::vec3 const& position);

    glm::vec3 const& getColor() const;
    void setColor(glm::vec3 const& color);

    glm::vec3 const& getAttenuation() const;

private:
    glm::vec3 position_;
    glm::vec3 color_;
    glm::vec3 attenuation_;
};

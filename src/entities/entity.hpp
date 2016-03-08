#pragma once
#include "models/textured_model.hpp"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
public:
    Entity(TexturedModel const* model,
           glm::vec3 const& position,
           glm::vec3 const& rotation,
           glm::vec3 const& scale,
           int textureIndex=0);

    void move(glm::vec3 const& translation);
    void rotate(glm::vec3 const& rotation);
    void scale(glm::vec3 const& scale);

    float getTextureXOffset() const;
    float getTextureYOffset() const;

    TexturedModel const* getModel() const;
    void setModel(TexturedModel const* model);
    glm::vec3 const& getPosition() const;
    void setPosition(glm::vec3 const& position);
    glm::vec3 const& getRotation() const;
    void setRotation(glm::vec3 const& rotation);
    glm::vec3 const& getScale() const;
    void setScale(glm::vec3 const& scale);

private:
    TexturedModel const* model_;
    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;
    int textureIndex_;
};

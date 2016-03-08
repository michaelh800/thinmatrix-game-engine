#include "entities/entity.hpp"


Entity::Entity(TexturedModel const* model,
    glm::vec3 const& position,
    glm::vec3 const& rotation,
    glm::vec3 const& scale,
    int textureIndex
)
    : model_(model)
    , position_(position)
    , rotation_(rotation)
    , scale_(scale)
    , textureIndex_(textureIndex)
{ }

void Entity::move(glm::vec3 const& translation) {
    position_ += translation;
}

void Entity::rotate(glm::vec3 const& rotation) {
    rotation_ += rotation;
}

void Entity::scale(glm::vec3 const& scale) {
    scale_ *= scale;
}

float Entity::getTextureXOffset() const {
    int column = textureIndex_ % model_->getModelTexture().getNumberOfRows();
    return (float) column / model_->getModelTexture().getNumberOfRows();
}

float Entity::getTextureYOffset() const {
    int row = textureIndex_ / model_->getModelTexture().getNumberOfRows();
    return (float) row / model_->getModelTexture().getNumberOfRows();

}

TexturedModel const* Entity::getModel() const { return model_; }
void Entity::setModel(TexturedModel const* model) { model_ = model; }

glm::vec3 const& Entity::getPosition() const { return position_; }
void Entity::setPosition(glm::vec3 const& position) { position_ = position; }

glm::vec3 const& Entity::getRotation() const { return rotation_; }
void Entity::setRotation(glm::vec3 const& rotation) { rotation_ = rotation; }

glm::vec3 const& Entity::getScale() const { return scale_; }
void Entity::setScale(glm::vec3 const& scale) { scale_ = scale; }
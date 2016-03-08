#include "guis/gui_texture.hpp"


GuiTexture::GuiTexture(GLuint textureId, glm::vec2 position, glm::vec2 scale)
    : textureId_(textureId)
    , position_(position)
    , scale_(scale)
{ }

GLuint GuiTexture::getTextureId() const {
    return textureId_;
}

glm::vec2 const& GuiTexture::getPosition() const {
    return position_;
}

glm::vec2 const& GuiTexture::getScale() const {
    return scale_;
}

#pragma once
#include <GL/glew.h>
#include <glm/vec2.hpp>

class GuiTexture {
public:
    GuiTexture(GLuint textureId, glm::vec2 position, glm::vec2 scale);

    GLuint getTextureId() const;
    glm::vec2 const& getPosition() const;
    glm::vec2 const& getScale() const;

private:
    GLuint textureId_;
    glm::vec2 position_;
    glm::vec2 scale_;
};

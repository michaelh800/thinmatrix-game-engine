#include "textures/terrain_texture.hpp"


TerrainTexture::TerrainTexture(GLuint textureId)
    : textureId_(textureId)
{ }

GLuint TerrainTexture::getTextureId() const {
    return textureId_;
}

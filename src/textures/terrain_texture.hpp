#pragma once
#include <GL/glew.h>

class TerrainTexture {
public:
    TerrainTexture(GLuint textureId);

    GLuint getTextureId() const;

private:
    GLuint textureId_;
};

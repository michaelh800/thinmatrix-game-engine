#pragma once
#include <GL/glew.h>

class RawModel {
public:
    RawModel() = default;
    RawModel(GLuint vaoId, GLsizei vertexCount);

    GLuint getVaoId() const;
    GLsizei getVertexCount() const;

private:
    GLuint vaoId_;
    GLsizei vertexCount_;
};

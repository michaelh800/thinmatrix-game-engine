#include "models/raw_model.hpp"


RawModel::RawModel(GLuint vaoId, GLsizei vertexCount)
    : vaoId_(vaoId)
    , vertexCount_(vertexCount)
{ }

GLuint RawModel::getVaoId() const { return vaoId_; }

GLsizei RawModel::getVertexCount() const { return vertexCount_; }

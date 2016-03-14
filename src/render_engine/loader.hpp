#pragma once
#include "models/raw_model.hpp"
#include "toolbox/gl_handles.hpp"
#include <GL/glew.h>
#include <string>
#include <vector>

class Loader {
public:
    RawModel loadToVao(std::vector<GLfloat> const& positions,
                       std::vector<GLfloat> const& textureCoords,
                       std::vector<GLfloat> const& normals,
                       std::vector<GLuint>  const& indices);

    RawModel loadToVao(std::vector<GLfloat> const& positions, int dimensions);

    GLuint loadTexture(std::string const& textureFile);
    GLuint loadCubeMap(std::vector<std::string> const& textureFiles);

private:
    GLuint createVao();
    void bindIndexBuffer(std::vector<GLuint> const& indices);
    void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<GLfloat> const& data);
    void unbindVao();

    std::vector<gl::VertexArrayHandle> vaos_;
    std::vector<gl::BufferHandle>      vbos_;
    std::vector<gl::TextureHandle>     textures_;
};

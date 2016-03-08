#include "render_engine/loader.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


Loader::~Loader() {
    for (GLuint vaoId : vaoIds_) {
        glDeleteVertexArrays(1, &vaoId);
    }
    for (GLuint vboId : vboIds_) {
        glDeleteBuffers(1, &vboId);
    }
    for (GLuint texId : texIds_) {
        glDeleteTextures(1, &texId);
    }
}

RawModel Loader::loadToVao(std::vector<GLfloat> const& positions,
                           std::vector<GLfloat> const& textureCoords,
                           std::vector<GLfloat> const& normals,
                           std::vector<GLuint> const& indices)
{
    GLuint vaoId = createVao();
    bindIndexBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normals);
    unbindVao();
    return RawModel(vaoId, indices.size());
}

RawModel Loader::loadToVao(std::vector<GLfloat> const& positions, int dimensions) {
    GLuint vaoId = createVao();
    storeDataInAttributeList(0, dimensions, positions);
    unbindVao();
    return RawModel(vaoId, positions.size() / dimensions);
}

GLuint Loader::loadTexture(std::string const& textureFile) {
    sf::Image image;
    if (!image.loadFromFile(textureFile)) {
        std::cerr << "[ERROR]: Failed to load texture: " << textureFile << std::endl;
    }

    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        image.getSize().x,
        image.getSize().y,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image.getPixelsPtr()
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER, GL_LINEAR              );
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,     GL_REPEAT              );
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,     GL_REPEAT              );
    glTexEnvi(      GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,   GL_MODULATE            );
    texIds_.push_back(texId);
    return texId;
}

GLuint Loader::loadCubeMap(std::vector<std::string> const& textureFiles) {
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    for (GLuint i = 0; i < textureFiles.size(); i++) {
        sf::Image image;
        if (!image.loadFromFile(textureFiles[i])) {
            std::cerr << "[ERROR]: Failed to load texture: " << textureFiles[i] << std::endl;
        }

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            0,
            GL_RGB,
            image.getSize().x,
            image.getSize().y,
            0,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            image.getPixelsPtr()
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR       );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR       );
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,     GL_CLAMP_TO_EDGE);
    texIds_.push_back(texId);
    return texId;
}

GLuint Loader::createVao() {
    GLuint vaoId;
    glGenVertexArrays(1, &vaoId);
    vaoIds_.push_back(vaoId);
    glBindVertexArray(vaoId);
    return vaoId;
}

void Loader::bindIndexBuffer(std::vector<GLuint> const& indices) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    vboIds_.push_back(vboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<GLfloat> const& data) {
    GLuint vboId;
    glGenBuffers(1, &vboId);
    vboIds_.push_back(vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVao() {
    glBindVertexArray(0);
}

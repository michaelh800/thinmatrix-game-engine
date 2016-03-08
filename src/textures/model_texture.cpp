#include "textures/model_texture.hpp"


ModelTexture::ModelTexture(GLuint textureId)
    : textureId_(textureId)
    , shineDamper_(1.0f)
    , reflectivity_(0.0f)
    , hasTransparency_(false)
    , usesFakeLighting_(false)
{ }

GLuint ModelTexture::getTextureId() const {
    return textureId_;
}

GLfloat ModelTexture::getShineDamper() const {
    return shineDamper_;
}
void ModelTexture::setShineDamper(GLfloat shineDamper) {
    shineDamper_ = shineDamper;
}

GLfloat ModelTexture::getReflectivity() const {
    return reflectivity_;
}
void ModelTexture::setReflectivity(GLfloat reflectivity) {
    reflectivity_ = reflectivity;
}

GLboolean ModelTexture::hasTransparency() const {
    return hasTransparency_;
}
void ModelTexture::setTransparency(GLboolean hasTransparency) {
    hasTransparency_ = hasTransparency;
}

GLboolean ModelTexture::usesFakeLighting() const {
    return usesFakeLighting_;
}
void ModelTexture::setFakeLighting(GLboolean usesFakeLighting) {
    usesFakeLighting_ = usesFakeLighting;
}

int ModelTexture::getNumberOfRows() const {
    return numberOfRows_;
}
void ModelTexture::setNumberOfRows(int numberOfRows) {
    numberOfRows_ = numberOfRows;
}

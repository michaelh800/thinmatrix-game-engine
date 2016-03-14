#include "water/water_shader.hpp"


namespace {
    constexpr auto VERTEX_SHADER_FILE = "res/shaders/water.v.glsl";
    constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/water.f.glsl";
}

WaterShader::WaterShader()
    : Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
{
    initialize();
}

void WaterShader::bindAttributes() {
    bindAttribute(0, "position");
}

void WaterShader::getAllUniformLocations() {
    modelMatrixLocation_ = getUniformLocation("modelMatrix");
    viewMatrixLocation_ = getUniformLocation("viewMatrix");
    projectionMatrixLocation_ = getUniformLocation("projectionMatrix");
    reflectionTextureLocation_ = getUniformLocation("reflectionTexture");
    refractionTextureLocation_ = getUniformLocation("refractionTexture");
}

void WaterShader::loadModelMatrix(glm::mat4 const& matrix) const {
    loadMatrix(modelMatrixLocation_, matrix);
}

void WaterShader::loadViewMatrix(Camera const& camera) const {
    loadMatrix(viewMatrixLocation_, camera.getViewMatrix());
}

void WaterShader::loadProjectionMatrix(glm::mat4 const& matrix) const {
    loadMatrix(projectionMatrixLocation_, matrix);
}

void WaterShader::connectTextureUnits() const {
    loadInteger(reflectionTextureLocation_, 0);
    loadInteger(refractionTextureLocation_, 1);
}

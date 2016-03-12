#include "skybox/skybox_shader.hpp"
#include "render_engine/display_manager.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>


namespace {
    constexpr auto VERTEX_SHADER_FILE = "res/shaders/skybox.v.glsl";
    constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/skybox.f.glsl";
    constexpr float ROTATE_SPEED = 1.0f;
}

SkyboxShader::SkyboxShader()
    : Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
{
    linkShaders();
}

void SkyboxShader::bindAttributes() {
    bindAttribute(0, "position");
}

void SkyboxShader::getAllUniformLocations() {
    viewMatrixLocation_ = getUniformLocation("viewMatrix");
    projectionMatrixLocation_ = getUniformLocation("projectionMatrix");
    fogColorLocation_ = getUniformLocation("fogColor");
    cubeMapLocation_ = getUniformLocation("cubeMap");
    cubeMap2Location_ = getUniformLocation("cubeMap2");
    blendFactorLocation_ = getUniformLocation("blendFactor");
}

void SkyboxShader::loadViewMatrix(Camera const& camera) {
    glm::mat4 matrix = camera.getViewMatrix();
    matrix[3] = glm::vec4{0.0, 0.0, 0.0, matrix[3][3]};
    rotation_ += ROTATE_SPEED * DisplayManager::getFrameTime().asSeconds();
    matrix = glm::rotate(matrix, glm::radians(rotation_), {0, 1, 0});
    loadMatrix(viewMatrixLocation_, matrix);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 const& matrix) const {
    loadMatrix(projectionMatrixLocation_, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 const& color) const {
    loadVector3(fogColorLocation_, color);
}

void SkyboxShader::loadBlendFactor(float blendFactor) const {
    loadFloat(blendFactorLocation_, blendFactor);
}

void SkyboxShader::connectTextureUnits() const {
    loadInteger(cubeMapLocation_, 0);
    loadInteger(cubeMap2Location_, 1);
}

#include "skybox/skybox_shader.hpp"


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
}

void SkyboxShader::loadViewMatrix(Camera const& camera) const {
    glm::mat4 matrix = camera.getViewMatrix();
    matrix[3] = glm::vec4{0.0, 0.0, 0.0, matrix[3][3]};
    loadMatrix(viewMatrixLocation_, matrix);
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 const& matrix) const {
    loadMatrix(projectionMatrixLocation_, matrix);
}

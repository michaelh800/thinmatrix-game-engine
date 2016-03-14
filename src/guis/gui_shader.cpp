#include "guis/gui_shader.hpp"


GuiShader::GuiShader()
    : Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
{
    initialize();
}

void GuiShader::bindAttributes() {
    bindAttribute(0, "position");
}

void GuiShader::getAllUniformLocations() {
    transformationMatrixLocation_ = getUniformLocation("transformationMatrix");
}

void GuiShader::loadTransformationMatrix(glm::mat4 const& matrix) const {
    loadMatrix(transformationMatrixLocation_, matrix);
}

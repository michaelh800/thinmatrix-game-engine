#pragma once
#include "shaders/shader.hpp"

class GuiShader final : public Shader {
public:
    GuiShader();

    void loadTransformationMatrix(glm::mat4 const& matrix) const;

protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    static constexpr auto VERTEX_SHADER_FILE = "res/shaders/gui.v.glsl";
    static constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/gui.f.glsl";

    GLint transformationMatrixLocation_;
};

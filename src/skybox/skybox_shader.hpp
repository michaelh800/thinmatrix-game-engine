#pragma once
#include "shaders/shader.hpp"
#include "entities/camera.hpp"

class SkyboxShader final : public Shader {
public:
    SkyboxShader();

    void loadViewMatrix(Camera const& camera) const;
    void loadProjectionMatrix(glm::mat4 const& matrix) const;

protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    static constexpr auto VERTEX_SHADER_FILE = "res/shaders/skybox.v.glsl";
    static constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/skybox.f.glsl";

    GLint viewMatrixLocation_;
    GLint projectionMatrixLocation_;
};

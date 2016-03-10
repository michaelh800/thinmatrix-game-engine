#pragma once
#include "shaders/shader.hpp"
#include "entities/camera.hpp"

class SkyboxShader final : public Shader {
public:
    SkyboxShader();

    void loadViewMatrix(Camera const& camera);
    void loadProjectionMatrix(glm::mat4 const& matrix) const;
    void loadFogColor(glm::vec3 const& color) const;
    void loadBlendFactor(float blendFactor) const;
    void connectTextureUnits() const;

protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    GLint viewMatrixLocation_;
    GLint projectionMatrixLocation_;
    GLint fogColorLocation_;
    GLint cubeMapLocation_;
    GLint cubeMap2Location_;
    GLint blendFactorLocation_;
    float rotation_ = 0.0f;
};

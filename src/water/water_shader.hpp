#pragma once
#include "shaders/shader.hpp"
#include "entities/camera.hpp"

class WaterShader final : public Shader {
public:
    WaterShader();

    void loadModelMatrix(glm::mat4 const& matrix) const;
    void loadViewMatrix(Camera const& camera) const;
    void loadProjectionMatrix(glm::mat4 const& matrix) const;
    void connectTextureUnits() const;

protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    GLint modelMatrixLocation_;
    GLint viewMatrixLocation_;
    GLint projectionMatrixLocation_;
    GLint reflectionTextureLocation_;
    GLint refractionTextureLocation_;
};

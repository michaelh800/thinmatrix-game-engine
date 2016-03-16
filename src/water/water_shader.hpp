#pragma once
#include "shaders/shader.hpp"
#include "entities/light.hpp"
#include "entities/camera.hpp"

class WaterShader final : public Shader {
public:
    WaterShader();

    void loadModelMatrix(glm::mat4 const& matrix) const;
    void loadViewMatrix(Camera& camera) const;
    void loadProjectionMatrix(glm::mat4 const& matrix) const;
    void loadMoveFactor(GLfloat moveFactor) const;
    void loadLight(Light const& sun) const;
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
    GLint dudvMapLocation_;
    GLint normalMapLocation_;
    GLint moveFactorLocation_;
    GLint cameraPositionLocation_;
    GLint lightPositionLocation_;
    GLint lightColorLocation_;
};

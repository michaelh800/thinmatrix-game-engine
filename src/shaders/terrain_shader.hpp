#pragma once
#include "shaders/shader.hpp"
#include "entities/light.hpp"
#include "entities/camera.hpp"
#include <GL/glew.h>
#include <vector>

class TerrainShader final : public Shader {
public:
    TerrainShader();

    void loadTransformationMatrix(glm::mat4 const& matrix) const;
    void loadViewMatrix(Camera const& camera) const;
    void loadProjectionMatrix(glm::mat4 const& matrix) const;
    void loadLights(std::vector<Light> const& lights) const;
    void loadShineVariables(GLfloat shineDamper, GLfloat reflectivity) const;
    void loadSkyColor(glm::vec3 const& rgbColor) const;
    void loadClipPlane(glm::vec4 const& plane) const;
    void connectTextureUnits() const;

protected:
    virtual void bindAttributes() override;
    virtual void getAllUniformLocations() override;

private:
    static constexpr int MAX_LIGHTS = 4;
    GLint transformationMatrixLocation_;
    GLint viewMatrixLocation_;
    GLint projectionMatrixLocation_;
    GLint lightPositionLocation_[MAX_LIGHTS];
    GLint lightColorLocation_[MAX_LIGHTS];
    GLint attenuationLocation_[MAX_LIGHTS];
    GLint shineDamperLocation_;
    GLint reflectivityLocation_;
    GLint skyColorLocation_;
    GLint backgroundTextureLocation_;
    GLint rTextureLocation_;
    GLint gTextureLocation_;
    GLint bTextureLocation_;
    GLint blendMapLocation_;
    GLint planeLocation_;
};

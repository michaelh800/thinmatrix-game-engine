#pragma once
#include "render_engine/loader.hpp"
#include "entities/camera.hpp"
#include "models/raw_model.hpp"
#include "skybox/skybox_shader.hpp"
#include <GL/glew.h>

class SkyboxRenderer {
public:
    SkyboxRenderer(Loader &loader);

    void render(Camera const& camera) const;
    void loadProjectionMatrix(glm::mat4 const& projectionMatrix) const;

private:
    RawModel cube_;
    GLuint textureId_;
    SkyboxShader shader_;
};

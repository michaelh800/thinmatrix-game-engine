#pragma once
#include "render_engine/loader.hpp"
#include "entities/camera.hpp"
#include "models/raw_model.hpp"
#include "skybox/skybox_shader.hpp"
#include <GL/glew.h>

class SkyboxRenderer {
public:
    SkyboxRenderer(Loader &loader);

    void render(Camera const& camera, glm::vec3 const& fogColor);
    void loadProjectionMatrix(glm::mat4 const& projectionMatrix) const;

private:
    void bindTextures();

    RawModel cube_;
    GLuint dayTextureId_;
    GLuint nightTextureId_;
    SkyboxShader shader_;
    float time_ = 0.0f;
};

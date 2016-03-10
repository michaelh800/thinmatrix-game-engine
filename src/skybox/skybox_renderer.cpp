#include "skybox/skybox_renderer.hpp"
#include "render_engine/display_manager.hpp"
#include <cmath>
#include <string>
#include <vector>


namespace {
    constexpr float SIZE = 500.0f;

    const std::vector<GLfloat> VERTICES {
        -SIZE,  SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,

        -SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE, -SIZE,  SIZE,

         SIZE, -SIZE, -SIZE,
         SIZE, -SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
         SIZE,  SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,

        -SIZE, -SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
         SIZE, -SIZE,  SIZE,
        -SIZE, -SIZE,  SIZE,

        -SIZE,  SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,
         SIZE,  SIZE,  SIZE,
         SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE,  SIZE,
        -SIZE,  SIZE, -SIZE,

        -SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE,  SIZE,
         SIZE, -SIZE,  SIZE
    };

    const std::vector<std::string> DAY_TEXTURE_FILES {
        "res/textures/skybox/day/right.png",
        "res/textures/skybox/day/left.png",
        "res/textures/skybox/day/top.png",
        "res/textures/skybox/day/bottom.png",
        "res/textures/skybox/day/back.png",
        "res/textures/skybox/day/front.png"
    };

    const std::vector<std::string> NIGHT_TEXTURE_FILES {
        "res/textures/skybox/night/right.png",
        "res/textures/skybox/night/left.png",
        "res/textures/skybox/night/top.png",
        "res/textures/skybox/night/bottom.png",
        "res/textures/skybox/night/back.png",
        "res/textures/skybox/night/front.png"
    };
}


SkyboxRenderer::SkyboxRenderer(Loader &loader)
    : cube_(loader.loadToVao(VERTICES, 3))
    , dayTextureId_(loader.loadCubeMap(DAY_TEXTURE_FILES))
    , nightTextureId_(loader.loadCubeMap(NIGHT_TEXTURE_FILES))
{
    shader_.start();
    shader_.connectTextureUnits();
    shader_.stop();
}

void SkyboxRenderer::render(Camera const& camera, glm::vec3 const& fogColor) {
    shader_.start();
    shader_.loadViewMatrix(camera);
    shader_.loadFogColor(fogColor);
    glBindVertexArray(cube_.getVaoId());
    glEnableVertexAttribArray(0);
    bindTextures();
    glDrawArrays(GL_TRIANGLES, 0, cube_.getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader_.stop();
}

void SkyboxRenderer::loadProjectionMatrix(glm::mat4 const& projectionMatrix) const {
    shader_.start();
    shader_.loadProjectionMatrix(projectionMatrix);
    shader_.stop();
}

void SkyboxRenderer::bindTextures() {
    time_ += DisplayManager::getFrameTime().asMilliseconds();
    time_ = std::fmod(time_, 24000);
    float blendFactor = -((time_/1000.0f)-13)*((time_/1000.0f)-13) * 0.02f + 1;
    if (blendFactor < 0) blendFactor = 0;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, dayTextureId_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, nightTextureId_);
    shader_.loadBlendFactor(blendFactor);
}

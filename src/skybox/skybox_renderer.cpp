#include "skybox/skybox_renderer.hpp"
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

const std::vector<std::string> TEXTURE_FILES {
    "res/textures/skybox/right.png",
    "res/textures/skybox/left.png",
    "res/textures/skybox/top.png",
    "res/textures/skybox/bottom.png",
    "res/textures/skybox/back.png",
    "res/textures/skybox/front.png"
};

}


SkyboxRenderer::SkyboxRenderer(Loader &loader)
    : cube_(loader.loadToVao(VERTICES, 3))
    , textureId_(loader.loadCubeMap(TEXTURE_FILES))
{ }

void SkyboxRenderer::render(Camera const& camera) const {
    shader_.start();
    shader_.loadViewMatrix(camera);
    glBindVertexArray(cube_.getVaoId());
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId_);
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

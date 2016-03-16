#include "water/water_renderer.hpp"
#include "render_engine/display_manager.hpp"
#include "toolbox/math.hpp"
#include <cmath>


namespace {
    constexpr auto DUDV_MAP = "res/textures/water/waterDUDV.png";
    constexpr auto NORMAL_MAP = "res/textures/water/normalMap.png";
    constexpr float WAVE_SPEED = 0.03f;
    const std::vector<GLfloat> POSITIONS
        { -1, -1, -1,  1, 1, -1, 1, -1, -1,  1, 1,  1 };
}

constexpr float WaterTile::TILE_SIZE;

WaterRenderer::WaterRenderer(Loader &loader, glm::mat4 const& projection,
    WaterFrameBuffers const& fbos)
    : quad_(loader.loadToVao(POSITIONS, 2))
    , fbos_(fbos)
    , dudvTextureId_(loader.loadTexture(DUDV_MAP))
    , normalMapTextureId_(loader.loadTexture(NORMAL_MAP))
{
    shader_.start();
    shader_.connectTextureUnits();
    shader_.loadProjectionMatrix(projection);
    shader_.stop();
}

void WaterRenderer::render(std::vector<WaterTile> const& water, Camera& camera,
    Light const& sun)
{
    prepareRender(camera, sun);
    for (WaterTile const& tile : water) {
        glm::mat4 modelMatrix = Math::createTransformationMatrix(
            glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()),
            glm::vec3(0),
            glm::vec3(WaterTile::TILE_SIZE));
        shader_.loadModelMatrix(modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, quad_.getVertexCount());
    }
    unbind();
}

void WaterRenderer::prepareRender(Camera& camera, Light const& sun) {
    shader_.start();
    shader_.loadViewMatrix(camera);
    shader_.loadLight(sun);
    moveFactor_ += WAVE_SPEED * DisplayManager::getFrameTime().asSeconds();
    moveFactor_ = std::fmod(moveFactor_, 1);
    shader_.loadMoveFactor(moveFactor_);
    glBindVertexArray(quad_.getVaoId());
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbos_.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbos_.getRefractionTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dudvTextureId_);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normalMapTextureId_);
}

void WaterRenderer::unbind() const {
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader_.stop();
}

void WaterRenderer::loadProjectionMatrix(glm::mat4 const& projection) const {
    shader_.start();
    shader_.loadProjectionMatrix(projection);
    shader_.stop();
}

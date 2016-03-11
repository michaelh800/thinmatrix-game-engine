#include "water/water_renderer.hpp"
#include "toolbox/math.hpp"


namespace {
    const std::vector<GLfloat> VERTICES{ -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 };
}
constexpr float WaterTile::TILE_SIZE;

WaterRenderer::WaterRenderer(Loader &loader, glm::mat4 const& projection)
    : quad_(loader.loadToVao(VERTICES, 2))
{
    loadProjectionMatrix(projection);
}

void WaterRenderer::render(std::vector<WaterTile> const& water,
    Camera const& camera) const
{
    prepareRender(camera);
    for (WaterTile const& tile : water) {
        glm::mat4 modelMatrix = Math::createTransformationMatrix(
            glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()),
            glm::vec3(0, 0, 0),
            glm::vec3(WaterTile::TILE_SIZE, WaterTile::TILE_SIZE, WaterTile::TILE_SIZE));
        shader_.loadModelMatrix(modelMatrix);
        glDrawArrays(GL_TRIANGLES, 0, quad_.getVertexCount());
    }
}

void WaterRenderer::prepareRender(Camera const& camera) const {
    shader_.start();
    shader_.loadViewMatrix(camera);
    glBindVertexArray(quad_.getVaoId());
    glEnableVertexAttribArray(0);
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

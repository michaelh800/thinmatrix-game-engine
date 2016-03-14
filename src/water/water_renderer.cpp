#include "water/water_renderer.hpp"
#include "toolbox/math.hpp"


namespace {
    const std::vector<GLfloat> POSITIONS {
        -1, -1,
        -1,  1,
         1, -1,
         1, -1,
        -1,  1,
         1,  1
    };
}

constexpr float WaterTile::TILE_SIZE;

WaterRenderer::WaterRenderer(Loader &loader, glm::mat4 const& projection,
    WaterFrameBuffers const& fbos)
    : quad_(loader.loadToVao(POSITIONS, 2))
    , fbos_(fbos)
{
    shader_.start();
    shader_.connectTextureUnits();
    shader_.loadProjectionMatrix(projection);
    shader_.stop();
}

void WaterRenderer::render(std::vector<WaterTile> const& water,
    Camera const& camera) const
{
    prepareRender(camera);
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

void WaterRenderer::prepareRender(Camera const& camera) const {
    shader_.start();
    shader_.loadViewMatrix(camera);
    glBindVertexArray(quad_.getVaoId());
    glEnableVertexAttribArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbos_.getReflectionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbos_.getRefractionTexture());
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

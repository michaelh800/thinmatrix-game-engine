#include "render_engine/terrain_renderer.hpp"
#include "render_engine/master_renderer.hpp"
#include "toolbox/math.hpp"


TerrainRenderer::TerrainRenderer(TerrainShader const* shader)
    : shader_(shader)
{
    shader_->start();
    shader_->connectTextureUnits();
    shader_->stop();
}

void TerrainRenderer::render(std::vector<Terrain const*> const& terrains) const {
    for (const auto& terrain : terrains) {
        prepareTerrain(terrain);
        loadModelMatrix(terrain);
        glDrawElements(GL_TRIANGLES, terrain->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTerrain();
    }
}

void TerrainRenderer::loadProjectionMatrix(glm::mat4 const& projectionMatrix) const {
    shader_->start();
    shader_->loadProjectionMatrix(projectionMatrix);
    shader_->stop();
}

void TerrainRenderer::prepareTerrain(Terrain const* terrain) const {
    glBindVertexArray(terrain->getRawModel().getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    bindTextures(terrain);
    shader_->loadShineVariables(1, 0);
}

void TerrainRenderer::bindTextures(Terrain const* terrain) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack().getBackgroundTexture().getTextureId());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack().getRTexture().getTextureId());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack().getGTexture().getTextureId());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack().getBTexture().getTextureId());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap().getTextureId());
}

void TerrainRenderer::unbindTerrain() const {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain const* terrain) const {
     glm::mat4 transformationMatrix = Math::createTransformationMatrix(
        glm::vec3(terrain->getX(), 0.0f, terrain->getZ()),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f));
    shader_->loadTransformationMatrix(transformationMatrix);
}


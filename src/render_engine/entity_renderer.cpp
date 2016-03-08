#include "render_engine/entity_renderer.hpp"
#include "render_engine/master_renderer.hpp"
#include "toolbox/math.hpp"


EntityRenderer::EntityRenderer(StaticShader const* shader)
    : shader_(shader)
{ }

void EntityRenderer::render(EntityMap const& entities) const {
    for (auto const& batch : entities) {
        prepareTexturedModel(batch.first);
        for (auto const& entity : batch.second) {
            prepareInstance(entity);
            glDrawElements(GL_TRIANGLES, batch.first->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }
}

void EntityRenderer::loadProjectionMatrix(glm::mat4 const& projectionMatrix) const {
    shader_->start();
    shader_->loadProjectionMatrix(projectionMatrix);
    shader_->stop();
}

void EntityRenderer::prepareTexturedModel(TexturedModel const* texturedModel) const {
    glBindVertexArray(texturedModel->getRawModel().getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    ModelTexture const& texture = texturedModel->getModelTexture();
    if (texture.hasTransparency()) MasterRenderer::disableCulling();
    shader_->loadNumberOfRows(texture.getNumberOfRows());
    shader_->loadFakeLightingVariable(texture.usesFakeLighting());
    shader_->loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getTextureId());
}

void EntityRenderer::unbindTexturedModel() const {
    MasterRenderer::enableCulling();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity const* entity) const {
    glm::mat4 transformationMatrix = Math::createTransformationMatrix(
        entity->getPosition(), entity->getRotation(), entity->getScale());
    shader_->loadTransformationMatrix(transformationMatrix);
    shader_->loadOffset(glm::vec2(entity->getTextureXOffset(), entity->getTextureYOffset()));
}

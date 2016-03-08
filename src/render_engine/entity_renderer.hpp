#pragma once
#include "entities/entity.hpp"
#include "shaders/static_shader.hpp"
#include <unordered_map>
#include <vector>

class EntityRenderer {
public:
    using EntityMap = std::unordered_map<TexturedModel const*, std::vector<Entity const*>>;

    EntityRenderer(StaticShader const* shader);

    void render(EntityMap const& entities) const;
    void loadProjectionMatrix(glm::mat4 const& projectionMatrix) const;

private:
    StaticShader const* shader_;

    void prepareTexturedModel(TexturedModel const* texturedModel) const;
    void unbindTexturedModel() const;
    void prepareInstance(Entity const* entity) const;
};

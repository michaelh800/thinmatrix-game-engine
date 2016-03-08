#pragma once
#include "terrain/terrain.hpp"
#include "shaders/terrain_shader.hpp"
#include <vector>

class TerrainRenderer {
public:
    TerrainRenderer(TerrainShader const* shader);

    void render(std::vector<Terrain const*> const& terrains) const;
    void loadProjectionMatrix(glm::mat4 const& projectionMatrix) const;

private:
    TerrainShader const* shader_;

    void prepareTerrain(Terrain const* terrain) const;
    void bindTextures(Terrain const* terrain) const;
    void unbindTerrain() const;
    void loadModelMatrix(Terrain const* terrain) const;
};

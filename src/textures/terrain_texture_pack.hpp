#pragma once
#include "textures/terrain_texture.hpp"

class TerrainTexturePack {
public:
    TerrainTexturePack(
        TerrainTexture backgroundTexture,
        TerrainTexture rTexture,
        TerrainTexture gTexture,
        TerrainTexture bTexture);

    TerrainTexture const& getBackgroundTexture() const;
    TerrainTexture const& getRTexture() const;
    TerrainTexture const& getGTexture() const;
    TerrainTexture const& getBTexture() const;

private:
    TerrainTexture backgroundTexture_;
    TerrainTexture rTexture_;
    TerrainTexture gTexture_;
    TerrainTexture bTexture_;
};

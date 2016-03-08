#include "textures/terrain_texture_pack.hpp"


TerrainTexturePack::TerrainTexturePack(
    TerrainTexture backgroundTexture,
    TerrainTexture rTexture,
    TerrainTexture gTexture,
    TerrainTexture bTexture
)
    : backgroundTexture_(backgroundTexture)
    , rTexture_(rTexture)
    , gTexture_(gTexture)
    , bTexture_(bTexture)
{ }

TerrainTexture const& TerrainTexturePack::getBackgroundTexture() const {
    return backgroundTexture_;
}

TerrainTexture const& TerrainTexturePack::getRTexture() const {
    return rTexture_;
}

TerrainTexture const& TerrainTexturePack::getGTexture() const {
    return gTexture_;
}

TerrainTexture const& TerrainTexturePack::getBTexture() const {
    return bTexture_;
}

#pragma once
#include "render_engine/loader.hpp"
#include "textures/terrain_texture_pack.hpp"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <glm/vec3.hpp>
#include <string>

class Terrain {
public:
    Terrain(GLfloat x, GLfloat z, Loader& loader, TerrainTexturePack texturePack,
        TerrainTexture blendMap, const std::string& heightMap);

    GLfloat getX() const;
    GLfloat getZ() const;
    RawModel const& getRawModel() const;
    TerrainTexturePack const& getTexturePack() const;
    TerrainTexture const& getBlendMap() const;

    float getHeightOfTerrain(float worldX, float worldZ) const;

private:
    std::vector<std::vector<float>> heights_;

    GLfloat x_;
    GLfloat z_;
    RawModel model_;
    TerrainTexturePack texturePack_;
    TerrainTexture blendMap_;

    RawModel generateTerrain(Loader& loader, const std::string& heightMap);
    glm::vec3 calculateNormal(unsigned int x, unsigned int y, sf::Image const& image);
    GLfloat getHeight(unsigned int x, unsigned int y, sf::Image const& image);
};

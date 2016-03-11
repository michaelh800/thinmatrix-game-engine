#include "terrain/terrain.hpp"
#include "toolbox/math.hpp"
#include <cstdio>
#include <cmath>
#include <vector>


namespace {
    constexpr GLfloat SIZE = 400.0f;
    constexpr GLfloat MAX_HEIGHT = 40.0f;
    constexpr GLfloat MAX_PIXEL_COLOR = 16777216.0f;
}

Terrain::Terrain(GLfloat x, GLfloat z, Loader& loader,TerrainTexturePack texturePack,
    TerrainTexture blendMap, const std::string& heightMap
)
    : x_(x * SIZE)
    , z_(z * SIZE)
    , model_(generateTerrain(loader, heightMap))
    , texturePack_(texturePack)
    , blendMap_(blendMap)
{ }

GLfloat Terrain::getX() const { return x_; }
GLfloat Terrain::getZ() const { return z_; }
RawModel const& Terrain::getRawModel() const { return model_; }
TerrainTexturePack const& Terrain::getTexturePack() const { return texturePack_; }
TerrainTexture const& Terrain::getBlendMap() const { return blendMap_; }

float Terrain::getHeightOfTerrain(float worldX, float worldZ) const {
    float terrainX = worldX - x_;
    float terrainZ = worldZ - z_;
    float gridSquareSize = SIZE / (heights_.size() - 1);
    int gridX = terrainX / gridSquareSize;
    int gridZ = terrainZ / gridSquareSize;
    if (gridX < 0 || gridX + 1 >= (int)heights_.size() || gridZ < 0 || gridZ + 1 >= (int)heights_.size()) {
        return 0.0f;
    }
    float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
    float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;
    float height;
    if (xCoord <= (1 - zCoord)) {
        height = Math::barryCentric(
            glm::vec3(0, heights_[gridX][gridZ], 0),
            glm::vec3(1, heights_[gridX + 1][gridZ], 0),
            glm::vec3(0, heights_[gridX][gridZ + 1], 1),
            glm::vec2(xCoord, zCoord));
    } else {
        height = Math::barryCentric(
            glm::vec3(1, heights_[gridX + 1][gridZ], 0),
            glm::vec3(1, heights_[gridX + 1][gridZ + 1], 1),
            glm::vec3(0, heights_[gridX][gridZ + 1], 1),
            glm::vec2(xCoord, zCoord));
    }
    return height;
}

RawModel Terrain::generateTerrain(Loader& loader, const std::string& heightMap) {
    sf::Image image;
    if (!image.loadFromFile(heightMap)) {
        printf("[ERROR]: Failed to load height map: %s\n", heightMap.c_str());
    }

    int VERTEX_COUNT = image.getSize().y;

    heights_ = std::vector<std::vector<float>>(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT));

    int count = VERTEX_COUNT * VERTEX_COUNT;
    std::vector<GLfloat> positions(count * 3);
    std::vector<GLfloat> texCoords(count * 2);
    std::vector<GLfloat> normals(count * 3);
    std::vector<GLuint>  indices(6 * (VERTEX_COUNT-1) * (VERTEX_COUNT-1));
    int vertexPointer = 0;
    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            positions[vertexPointer*3] = (GLfloat)j / (VERTEX_COUNT-1) * SIZE;
            positions[vertexPointer*3 + 1] = heights_[j][i] = getHeight(j, i, image);
            positions[vertexPointer*3 + 1] = getHeight(j, i, image);
            positions[vertexPointer*3 + 2] = (GLfloat)i / (VERTEX_COUNT-1) * SIZE;
            texCoords[vertexPointer*2] = (GLfloat)j / (VERTEX_COUNT-1);
            texCoords[vertexPointer*2 + 1] = (GLfloat)i / (VERTEX_COUNT-1);
            glm::vec3 normal = calculateNormal(j, i, image);
            normals[vertexPointer*3] = normal.x;
            normals[vertexPointer*3 + 1] = normal.y;
            normals[vertexPointer*3 + 2] = normal.z;
            ++vertexPointer;
        }
    }
    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT-1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT-1; gx++) {
            GLuint topLeft = (gz*VERTEX_COUNT)+gx;
            GLuint topRight = topLeft + 1;
            GLuint bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
            GLuint bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader.loadToVao(positions, texCoords, normals, indices);
}

glm::vec3 Terrain::calculateNormal(unsigned int x, unsigned int y, sf::Image const& image) {
    float heightL = getHeight(x - 1, y, image);
    float heightR = getHeight(x + 1, y, image);
    float heightD = getHeight(x, y - 1, image);
    float heightU = getHeight(x, y + 1, image);
    return glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));
}

GLfloat Terrain::getHeight(unsigned int x, unsigned int y, sf::Image const& image) {
    if (x > image.getSize().y || y > image.getSize().y) {
        return 0.0f;
    }

    sf::Color pixel = image.getPixel(x, y);
    int color = (pixel.a << 24)
              | (pixel.r << 16)
              | (pixel.g << 8)
              | (pixel.b << 0);
    GLfloat height = color;
    height += MAX_PIXEL_COLOR / 2.0f;
    height /= MAX_PIXEL_COLOR / 2.0f;
    height *= MAX_HEIGHT;
    return height;
}

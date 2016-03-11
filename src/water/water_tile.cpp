#include "water/water_tile.hpp"


WaterTile::WaterTile(float x, float z, float height)
    : x_(x)
    , z_(z)
    , height_(height)
{ }

float WaterTile::getX() const {
    return x_;
}

float WaterTile::getZ() const {
    return z_;
}

float WaterTile::getHeight() const {
    return height_;
}

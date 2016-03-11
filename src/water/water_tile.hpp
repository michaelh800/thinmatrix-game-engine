#pragma once

class WaterTile {
public:
    WaterTile(float x, float z, float height);

    float getX() const;
    float getZ() const;
    float getHeight() const;

    static constexpr float TILE_SIZE = 200.0f;

private:
    float x_, z_;
    float height_;
};

#pragma once
#include "models/raw_model.hpp"
#include "textures/model_texture.hpp"

class TexturedModel {
public:
    TexturedModel() = default;
    TexturedModel(RawModel rawModel, ModelTexture modelTexture);

    RawModel const& getRawModel() const;
    ModelTexture const& getModelTexture() const;

private:
    RawModel rawModel_;
    ModelTexture modelTexture_;
};

#include "models/textured_model.hpp"


TexturedModel::TexturedModel(RawModel rawModel, ModelTexture modelTexture)
    : rawModel_(rawModel)
    , modelTexture_(modelTexture)
{ }

RawModel const& TexturedModel::getRawModel() const {
    return rawModel_;
}

ModelTexture const& TexturedModel::getModelTexture() const {
    return modelTexture_;
}

#pragma once
#include "water/water_shader.hpp"
#include "water/water_tile.hpp"
#include "water/water_frame_buffers.hpp"
#include "models/raw_model.hpp"
#include <vector>

class WaterRenderer {
public:
    WaterRenderer(
        Loader &loader,
        glm::mat4 const& projection,
        WaterFrameBuffers const& fbos);

    void render(std::vector<WaterTile> const& water, Camera const& camera) const;

private:
    void prepareRender(Camera const& camera) const;
    void unbind() const;
    void loadProjectionMatrix(glm::mat4 const& projection) const;

    RawModel quad_;
    WaterShader shader_{};
    WaterFrameBuffers const& fbos_;
};

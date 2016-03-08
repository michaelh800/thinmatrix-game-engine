#pragma once
#include "render_engine/loader.hpp"
#include "models/raw_model.hpp"
#include "guis/gui_texture.hpp"
#include "guis/gui_shader.hpp"
#include <vector>

class GuiRenderer {
public:
    GuiRenderer(Loader &loader);

    void render(std::vector<GuiTexture> const& guis);

private:
    RawModel quad_;
    GuiShader shader_;
};

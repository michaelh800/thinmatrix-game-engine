#pragma once
#include "render_engine/display_manager.hpp"
#include "render_engine/glew.hpp"
#include "render_engine/loader.hpp"
#include "entities/camera.hpp"
#include "entities/light.hpp"
#include "entities/entity.hpp"
#include "terrain/terrain.hpp"
#include "guis/gui_renderer.hpp"
#include "render_engine/master_renderer.hpp"
#include "toolbox/mouse_picker.hpp"
#include "water/water_renderer.hpp"
#include "water/water_tile.hpp"
#include "water/water_frame_buffers.hpp"
#include <vector>

class GameEngine {
public:
    GameEngine() = default;
    ~GameEngine();

    void doMainLoop();

private:
    DisplayManager          display_{};
    Glew                    glew_{};
    Loader                  loader_{};
    Camera                  camera_{true};
    std::vector<Light>      lights_;
    std::vector<Entity>     entities_;
    std::vector<Terrain>    terrains_;
    MasterRenderer          renderer_{loader_};
    MousePicker             picker_{camera_, renderer_.getProjectionMatrix()};
    GuiRenderer             guiRenderer_{loader_};
    std::vector<GuiTexture> guis_;
    WaterRenderer           waterRenderer_{loader_, renderer_.getProjectionMatrix()};
    std::vector<WaterTile>  waters_;
    WaterFrameBuffers       waterFbos_{};
};

#pragma once
#include "engine_tester/game.hpp"
#include "render_engine/display_manager.hpp"
#include "render_engine/glew.hpp"
#include "render_engine/master_renderer.hpp"
#include "toolbox/mouse_picker.hpp"

class GameEngine {
public:
    GameEngine() = default;
    ~GameEngine();
    void run();

private:
    DisplayManager display_{};
    Glew glew_{};
    Game game_{};
    MasterRenderer renderer_{game_.getLoader()};
    MousePicker picker_{game_.getCamera(), renderer_.getProjectionMatrix()};
};

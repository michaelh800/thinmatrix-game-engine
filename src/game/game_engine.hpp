#pragma once
#include "render_engine/display.hpp"
#include "render_engine/glew.hpp"
#include "render_engine/master_renderer.hpp"
#include "game/game.hpp"

class GameEngine {
public:
    GameEngine() = default;
    ~GameEngine();
    void run();

private:
    Display display_{};
    Glew glew_{};
    Game game_{};
    MasterRenderer renderer_{game_.getLoader()};
};

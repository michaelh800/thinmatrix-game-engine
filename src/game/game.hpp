#pragma once
#include "render_engine/master_renderer.hpp"
#include "render_engine/loader.hpp"
#include "render_engine/obj_loader.hpp"
#include "entities/camera.hpp"
#include "entities/light.hpp"
#include "entities/entity.hpp"
#include "terrain/terrain.hpp"
#include "guis/gui_renderer.hpp"
#include <vector>

class Game {
public:
    Game();

    void update();
    void render(MasterRenderer& renderer);

    Loader& getLoader();

private:
    Loader                  loader_;
    Camera                  camera_;
    std::vector<Light>      lights_;
    TexturedModel           lampModel_;
    TexturedModel           treeModel_;
    TexturedModel           fernModel_;
    std::vector<Entity>     entities_;
    std::vector<Terrain>    terrains_;
    GuiRenderer             gui_renderer_{loader_};
    std::vector<GuiTexture> guis_;
};

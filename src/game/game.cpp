#include "game/game.hpp"
#include "render_engine/obj_loader.hpp"


Game::Game() {
    // create terrain
    TerrainTexture backgroundTexture(loader_.loadTexture("res/textures/terrain/grass.png"));
    TerrainTexture rTexture(loader_.loadTexture("res/textures/terrain/mud.png"));
    TerrainTexture gTexture(loader_.loadTexture("res/textures/terrain/grassFlowers.png"));
    TerrainTexture bTexture(loader_.loadTexture("res/textures/terrain/path.png"));
    TerrainTexturePack texturePack(backgroundTexture, rTexture, gTexture, bTexture);
    TerrainTexture blendMap(loader_.loadTexture("res/textures/terrain/blendMap.png"));
    terrains_.push_back(Terrain(-0.5f, -0.5f, loader_, texturePack, blendMap, "res/textures/terrain/heightmap.png"));

    // set light positions
    glm::vec3 lightHeight = glm::vec3(0, 17, 0);
    glm::vec3 lightPos1 = glm::vec3(30, terrains_.front().getHeightOfTerrain(30, -125), -125);
    glm::vec3 lightPos2 = glm::vec3(30, terrains_.front().getHeightOfTerrain(30, -50), -50);
    glm::vec3 lightPos3 = glm::vec3(30, terrains_.front().getHeightOfTerrain(30, -200), -200);

    // add lights
    lights_.emplace_back(glm::vec3(0, 1000, -7000), glm::vec3(0.4f, 0.4f, 0.4f));
    lights_.emplace_back(lightPos1 + lightHeight, glm::vec3(2, 0, 0), glm::vec3(1.0f, 0.01f, 0.002f));
    lights_.emplace_back(lightPos2 + lightHeight, glm::vec3(0, 2, 2), glm::vec3(1.0f, 0.01f, 0.002f));
    lights_.emplace_back(lightPos3 + lightHeight, glm::vec3(2, 2, 0), glm::vec3(1.0f, 0.01f, 0.002f));

    // create lamp model
    ModelTexture lampTexture(loader_.loadTexture("res/textures/lamp/lamp.png"));
    lampTexture.setFakeLighting(true);
    lampTexture.setNumberOfRows(1);
    lampModel_ = TexturedModel(ObjLoader::loadObjModel("res/models/lamp/lamp.obj", loader_), lampTexture);

    // place lamp entities
    entities_.push_back(Entity(&lampModel_, lightPos1, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    entities_.push_back(Entity(&lampModel_, lightPos2, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
    entities_.push_back(Entity(&lampModel_, lightPos3, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

    // create tree model
    ModelTexture treeTexture(loader_.loadTexture("res/textures/pine/pine.png"));
    treeTexture.setNumberOfRows(1);
    treeModel_ = TexturedModel(ObjLoader::loadObjModel("res/models/pine/pine.obj", loader_), treeTexture);

    // create fern model
    ModelTexture fernTexture(loader_.loadTexture("res/textures/fern/fern_atlas.png"));
    fernTexture.setTransparency(true);
    fernTexture.setFakeLighting(true);
    fernTexture.setNumberOfRows(2);
    fernModel_ = TexturedModel(ObjLoader::loadObjModel("res/models/fern/fern.obj", loader_), fernTexture );

    // randomly place entities
    for (int x = -200; x <= 200; x += 20) {
        for (int z = -200; z <= 200; z += 20) {
            float random = (float)rand() / RAND_MAX;
            if (random < 0.1) {
                entities_.push_back(Entity(&fernModel_, glm::vec3(x, terrains_.front().getHeightOfTerrain(x, z), z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), rand()%4));
            }
            if (random > 0.8) {
                entities_.push_back(Entity(&treeModel_, glm::vec3(x, terrains_.front().getHeightOfTerrain(x, z), z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
            }
        }
    }

    // create guis
    GuiTexture guiTexture(loader_.loadTexture("res/textures/guis/thinmatrix.png"), glm::vec2(-0.75f, 0.9f), glm::vec2(0.25f, 0.25f));
    guis_.push_back(guiTexture);
}

void Game::update() {
    camera_.update(terrains_.front());
}

void Game::render(MasterRenderer& renderer) {
    for (const auto& entity : entities_) {
        renderer.processEntity(&entity);
    }
    for (const auto& terrain : terrains_) {
        renderer.processTerrain(&terrain);
    }
    renderer.render(lights_, camera_);
    gui_renderer_.render(guis_);
}

Loader& Game::getLoader() {
    return loader_;
}

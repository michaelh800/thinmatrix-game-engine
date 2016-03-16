#include "engine_tester/game_engine.hpp"
#include "render_engine/obj_loader.hpp"


GameEngine::~GameEngine() {
    display_.close();
}

void GameEngine::doMainLoop() {

    /* *********************************************************** */
    /*                        INITIALIZE                           */
    /* *********************************************************** */

    // create terrain
    TerrainTexture backgroundTexture(loader_.loadTexture("res/textures/terrain/grass.png"));
    TerrainTexture rTexture(loader_.loadTexture("res/textures/terrain/mud.png"));
    TerrainTexture gTexture(loader_.loadTexture("res/textures/terrain/grassFlowers.png"));
    TerrainTexture bTexture(loader_.loadTexture("res/textures/terrain/path.png"));
    TerrainTexturePack texturePack(backgroundTexture, rTexture, gTexture, bTexture);
    TerrainTexture blendMap(loader_.loadTexture("res/textures/terrain/blendMap.png"));
    terrains_.emplace_back(-0.5f, -0.5f, loader_, texturePack, blendMap, "res/textures/terrain/heightmap.png");

    // set light positions
    // glm::vec3 lightHeight = glm::vec3(0, 17, 0);
    // glm::vec3 lightPos1 = glm::vec3(-80, terrains_.front().getHeightOfTerrain(-80, -90), -90);
    // glm::vec3 lightPos2 = glm::vec3(65, terrains_.front().getHeightOfTerrain(65, -10), -10);
    // glm::vec3 lightPos3 = glm::vec3(-20, terrains_.front().getHeightOfTerrain(-20, 150), 150);

    // add lights
    lights_.emplace_back(glm::vec3(0, 1000, -1000), glm::vec3(0.8f, 0.8f, 0.8f));
    // lights_.emplace_back(lightPos1 + lightHeight, glm::vec3(2, 0, 0), glm::vec3(1.0f, 0.01f, 0.002f));
    // lights_.emplace_back(lightPos2 + lightHeight, glm::vec3(0, 2, 2), glm::vec3(1.0f, 0.01f, 0.002f));
    // lights_.emplace_back(lightPos3 + lightHeight, glm::vec3(2, 2, 0), glm::vec3(1.0f, 0.01f, 0.002f));

    // create lamp model
    // ModelTexture lampTexture(loader_.loadTexture("res/textures/lamp/lamp.png"));
    // lampTexture.setFakeLighting(true);
    // lampTexture.setNumberOfRows(1);
    // auto lamp = TexturedModel(ObjLoader::loadObjModel("res/models/lamp/lamp.obj", loader_), lampTexture);

    // place lamp entities
    // entities_.emplace_back(&lamp, lightPos1, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    // entities_.emplace_back(&lamp, lightPos2, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
    // entities_.emplace_back(&lamp, lightPos3, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

    // create tree model
    ModelTexture treeTexture(loader_.loadTexture("res/textures/pine/pine.png"));
    treeTexture.setNumberOfRows(1);
    auto tree = TexturedModel(ObjLoader::loadObjModel("res/models/pine/pine.obj", loader_), treeTexture);

    // create fern model
    ModelTexture fernTexture(loader_.loadTexture("res/textures/fern/fern_atlas.png"));
    fernTexture.setTransparency(true);
    fernTexture.setFakeLighting(true);
    fernTexture.setNumberOfRows(2);
    auto fern = TexturedModel(ObjLoader::loadObjModel("res/models/fern/fern.obj", loader_), fernTexture );

    // randomly place tree and fern entities
    for (int x = -200; x <= 200; x += 20) {
        for (int z = -200; z <= 200; z += 20) {
            float random = (float)rand() / RAND_MAX;
            float y = terrains_.front().getHeightOfTerrain(x, z);
            if (y >= 0.0f && random < 0.1) {
                entities_.emplace_back(&fern, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(1), rand()%4);
            }
            if (y >= 0.0f && random > 0.7) {
                entities_.emplace_back(&tree, glm::vec3(x, y, z), glm::vec3(0), glm::vec3(1));
            }
        }
    }

    // create guis
    guis_.emplace_back(loader_.loadTexture("res/textures/guis/thinmatrix.png"), glm::vec2(-0.75f, 0.9f), glm::vec2(0.25f));

    // create waters
    waters_.emplace_back(0.0f, 0.0f, 0.0f);


    /* *********************************************************** */
    /*                        MAIN LOOP                            */
    /* *********************************************************** */

    bool running = true;

    while (running) {
        sf::Event event;
        while (display_.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                display_.resize(event.size.width, event.size.height);
                renderer_.resetProjectionMatrix();
            }
        }

        camera_.update(terrains_.front());
        // picker_.update();
        // auto ray = picker_.getCurrentRay();

        glEnable(GL_CLIP_DISTANCE0);
        float waterHeight = waters_.front().getHeight();

        waterFbos_.bindReflectionFrameBuffer();
        float distance = 2.0f * (camera_.getPosition().y - waterHeight);
        camera_.getPosition().y -= distance;
        camera_.invertPitch();
        renderer_.renderScene(entities_, terrains_.front(), lights_, camera_, {0.0f, 1.0f, 0.0f, -waterHeight});
        camera_.getPosition().y += distance;
        camera_.invertPitch();

        waterFbos_.bindRefractionFrameBuffer();
        renderer_.renderScene(entities_, terrains_.front(), lights_, camera_, {0.0f, -1.0f, 0.0f, waterHeight});

        glDisable(GL_CLIP_DISTANCE0);

        waterFbos_.unbindCurrentFrameBuffer();
        renderer_.renderScene(entities_, terrains_.front(), lights_, camera_, {0, 0, 0, 0});
        waterRenderer_.render(waters_, camera_, lights_.front());
        guiRenderer_.render(guis_);
        display_.update();
    }
}

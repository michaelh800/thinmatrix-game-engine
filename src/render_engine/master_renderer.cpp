#include "render_engine/master_renderer.hpp"
#include "render_engine/display_manager.hpp"


namespace {
    constexpr float FOV = 70.0f;
    constexpr float NEAR_PLANE = 0.1f;
    constexpr float FAR_PLANE = 1000.0f;
    constexpr float RED = 0.5444f;
    constexpr float GREEN = 0.62f;
    constexpr float BLUE = 0.69f;
}

MasterRenderer::MasterRenderer(Loader& loader) : skyboxRenderer_(loader) {
    resetProjectionMatrix();
    enableCulling();
    glEnable(GL_DEPTH_TEST);
}

void MasterRenderer::prepare() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(RED, GREEN, BLUE, 1);
}

void MasterRenderer::render(std::vector<Light> const& lights, Camera const& camera) {
    prepare();
    entityShader_.start();
    entityShader_.loadSkyColor(glm::vec3{RED, GREEN, BLUE});
    entityShader_.loadLights(lights);
    entityShader_.loadViewMatrix(camera);
    entityRenderer_.render(entities_);
    entityShader_.stop();
    terrainShader_.start();
    terrainShader_.loadSkyColor(glm::vec3{RED, GREEN, BLUE});
    terrainShader_.loadLights(lights);
    terrainShader_.loadViewMatrix(camera);
    terrainRenderer_.render(terrains_);
    terrainShader_.stop();
    skyboxRenderer_.render(camera, glm::vec3{RED, GREEN, BLUE});
    entities_.clear();
    terrains_.clear();
}

void MasterRenderer::processEntity(Entity const* entity) {
    entities_[entity->getModel()].push_back(entity);
}

void MasterRenderer::processTerrain(Terrain const* terrain) {
    terrains_.push_back(terrain);
}

void MasterRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}

void MasterRenderer::resetProjectionMatrix() {
    projectionMatrix_ = glm::perspective(
        FOV, DisplayManager::getAspectRatio(), NEAR_PLANE, FAR_PLANE);
    entityRenderer_.loadProjectionMatrix(projectionMatrix_);
    terrainRenderer_.loadProjectionMatrix(projectionMatrix_);
    skyboxRenderer_.loadProjectionMatrix(projectionMatrix_);
}

glm::mat4 const& MasterRenderer::getProjectionMatrix() const {
    return projectionMatrix_;
}

void MasterRenderer::renderScene(std::vector<Entity> const& entities,
    Terrain const& terrain, std::vector<Light> const& lights, Camera const& camera)
{
    processTerrain(&terrain);
    for (Entity const& entity : entities) processEntity(&entity);
    render(lights, camera);
}

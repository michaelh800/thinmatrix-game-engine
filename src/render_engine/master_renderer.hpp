#pragma once
#include "render_engine/entity_renderer.hpp"
#include "render_engine/terrain_renderer.hpp"
#include "render_engine/loader.hpp"
#include "entities/light.hpp"
#include "entities/camera.hpp"
#include "skybox/skybox_renderer.hpp"
#include <glm/vec4.hpp>
#include <unordered_map>
#include <vector>

class MasterRenderer {
public:
    MasterRenderer(Loader& loader);

    void renderScene(
        std::vector<Entity> const& entities,
        Terrain const& terrain,
        std::vector<Light> const& lights,
        Camera const& camera,
        glm::vec4 const& cliPlane);

    void prepare() const;
    void render(
        std::vector<Light> const& lights,
        Camera const& camera,
        glm::vec4 const& cliPlane);

    void processEntity(Entity const* entity);
    void processTerrain(Terrain const* terrain);

    static void enableCulling();
    static void disableCulling();
    void resetProjectionMatrix();
    glm::mat4 const& getProjectionMatrix() const;

private:
    using EntityMap = std::unordered_map<TexturedModel const*, std::vector<Entity const*>>;

    glm::mat4 projectionMatrix_;
    StaticShader entityShader_{};
    TerrainShader terrainShader_{};
    EntityRenderer entityRenderer_{&entityShader_};
    TerrainRenderer terrainRenderer_{&terrainShader_};
    EntityMap entities_;
    std::vector<Terrain const*> terrains_;
    SkyboxRenderer skyboxRenderer_;
};

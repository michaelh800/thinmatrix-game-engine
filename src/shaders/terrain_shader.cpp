#include "shaders/terrain_shader.hpp"


namespace {
    constexpr auto VERTEX_SHADER_FILE = "res/shaders/terrain.v.glsl";
    constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/terrain.f.glsl";
}

TerrainShader::TerrainShader()
    : Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
{
    linkShaders();
}

void TerrainShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() {
    transformationMatrixLocation_ = getUniformLocation("transformationMatrix");
    viewMatrixLocation_ = getUniformLocation("viewMatrix");
    projectionMatrixLocation_ = getUniformLocation("projectionMatrix");
    shineDamperLocation_ = getUniformLocation("shineDamper");
    reflectivityLocation_ = getUniformLocation("reflectivity");
    skyColorLocation_ = getUniformLocation("skyColor");
    backgroundTextureLocation_ = getUniformLocation("backgroundTexture");
    rTextureLocation_ = getUniformLocation("rTexture");
    gTextureLocation_ = getUniformLocation("gTexture");
    bTextureLocation_ = getUniformLocation("bTexture");
    blendMapLocation_ = getUniformLocation("blendMap");

    for (int i = 0; i < MAX_LIGHTS; i++) {
        lightPositionLocation_[i] = getUniformLocation(
            std::string("lightPosition[" + std::to_string(i) + "]").c_str());
        lightColorLocation_[i] = getUniformLocation(
            std::string("lightColor[" + std::to_string(i) + "]").c_str());
        attenuationLocation_[i] = getUniformLocation(
            std::string("attenuation[" + std::to_string(i) + "]").c_str());
    }
}

void TerrainShader::loadTransformationMatrix(glm::mat4 const& matrix) const {
    loadMatrix(transformationMatrixLocation_, matrix);
}

void TerrainShader::loadViewMatrix(Camera const& camera) const {
    loadMatrix(viewMatrixLocation_, camera.getViewMatrix());
}

void TerrainShader::loadProjectionMatrix(glm::mat4 const& matrix) const {
    loadMatrix(projectionMatrixLocation_, matrix);
}

void TerrainShader::loadLights(std::vector<Light> const& lights) const {
    for (int i = 0; i < MAX_LIGHTS; i++) {
        if (i < (int)lights.size()) {
            loadVector3(lightPositionLocation_[i], lights[i].getPosition());
            loadVector3(lightColorLocation_[i], lights[i].getColor());
            loadVector3(attenuationLocation_[i], lights[i].getAttenuation());
        } else {
            loadVector3(lightPositionLocation_[i], glm::vec3(0, 0, 0));
            loadVector3(lightColorLocation_[i], glm::vec3(0, 0, 0));
            loadVector3(attenuationLocation_[i], glm::vec3(1, 0, 0));
        }
    }
}

void TerrainShader::loadShineVariables(GLfloat shineDamper, GLfloat reflectivity) const {
    loadFloat(shineDamperLocation_, shineDamper);
    loadFloat(reflectivityLocation_, reflectivity);
}

void TerrainShader::loadSkyColor(glm::vec3 const& rgbColor) const {
    loadVector3(skyColorLocation_, rgbColor);
}

void TerrainShader::connectTextureUnits() const {
    loadInteger(backgroundTextureLocation_, 0);
    loadInteger(rTextureLocation_, 1);
    loadInteger(gTextureLocation_, 2);
    loadInteger(bTextureLocation_, 3);
    loadInteger(blendMapLocation_, 4);
}

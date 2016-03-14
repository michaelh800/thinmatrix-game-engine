#include "shaders/static_shader.hpp"
#include "toolbox/math.hpp"


namespace {
    constexpr auto VERTEX_SHADER_FILE = "res/shaders/static.v.glsl";
    constexpr auto FRAGMENT_SHADER_FILE = "res/shaders/static.f.glsl";
}

StaticShader::StaticShader()
    : Shader(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE)
{
    initialize();
}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations() {
    transformationMatrixLocation_ = getUniformLocation("transformationMatrix");
    viewMatrixLocation_ = getUniformLocation("viewMatrix");
    projectionMatrixLocation_ = getUniformLocation("projectionMatrix");
    shineDamperLocation_ = getUniformLocation("shineDamper");
    reflectivityLocation_ = getUniformLocation("reflectivity");
    useFakeLightingLocation_ = getUniformLocation("useFakeLighting");
    skyColorLocation_ = getUniformLocation("skyColor");
    numberOfRowsLocation_ = getUniformLocation("numberOfRows");
    offsetLocation_ = getUniformLocation("offset");
    planeLocation_ = getUniformLocation("plane");

    for (int i = 0; i < MAX_LIGHTS; i++) {
        lightPositionLocation_[i] = getUniformLocation(
            std::string("lightPosition[" + std::to_string(i) + "]").c_str());
        lightColorLocation_[i] = getUniformLocation(
            std::string("lightColor[" + std::to_string(i) + "]").c_str());
        attenuationLocation_[i] = getUniformLocation(
            std::string("attenuation[" + std::to_string(i) + "]").c_str());
    }
}

void StaticShader::loadTransformationMatrix(glm::mat4 const& matrix) const {
    loadMatrix(transformationMatrixLocation_, matrix);
}

void StaticShader::loadViewMatrix(Camera const& camera) const {
    loadMatrix(viewMatrixLocation_, camera.getViewMatrix());
}

void StaticShader::loadProjectionMatrix(glm::mat4 const& matrix) const {
    loadMatrix(projectionMatrixLocation_, matrix);
}

void StaticShader::loadLights(std::vector<Light> const& lights) const {
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

void StaticShader::loadShineVariables(GLfloat shineDamper, GLfloat reflectivity) const {
    loadFloat(shineDamperLocation_, shineDamper);
    loadFloat(reflectivityLocation_, reflectivity);
}

void StaticShader::loadFakeLightingVariable(GLboolean useFakeLighting) const {
    loadInteger(useFakeLightingLocation_, useFakeLighting);
}

void StaticShader::loadSkyColor(glm::vec3 const& rgbColor) const {
    loadVector3(skyColorLocation_, rgbColor);
}

void StaticShader::loadNumberOfRows(int numberOfRows) const {
    loadFloat(numberOfRowsLocation_, (GLfloat) numberOfRows);
}

void StaticShader::loadOffset(glm::vec2 const& offset) const {
    loadVector2(offsetLocation_, offset);
}

void StaticShader::loadClipPlane(glm::vec4 const& plane) const {
    loadVector4(planeLocation_, plane);
}

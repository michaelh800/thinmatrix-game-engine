#include "water/water_frame_buffers.hpp"
#include "render_engine/display_manager.hpp"
#include "toolbox/debug.hpp"

namespace {
    constexpr int REFLECTION_WIDTH = 320, REFLECTION_HEIGHT = 1280;
    constexpr int REFRACTION_WIDTH = 180, REFRACTION_HEIGHT = 720;
}

WaterFrameBuffers::WaterFrameBuffers() {
    initializeReflectionFrameBuffer();
    initializeRefractionFrameBuffer();
}

void WaterFrameBuffers::bindReflectionFrameBuffer() const {
    bindFrameBuffer(reflectionFbo_, REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer() const {
    bindFrameBuffer(refractionFbo_, REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer() const {
    auto dimensions = DisplayManager::getWindow().getSize();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, dimensions.x, dimensions.y);
}

GLuint WaterFrameBuffers::getReflectionTexture() const {
    return reflectionTextureId_;
}

GLuint WaterFrameBuffers::getRefractionTexture() const {
    return refractionTextureId_;
}

GLuint WaterFrameBuffers::getRefractionDepthTexture() const {
    return refractionDepthTextureId_;
}

void WaterFrameBuffers::bindFrameBuffer(GLuint fbo, int width, int height) const {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

void WaterFrameBuffers::initializeReflectionFrameBuffer() {
    reflectionFbo_ = createFrameBuffer();
    reflectionTextureId_ = createColorTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionDepthBufferId_ = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initializeRefractionFrameBuffer() {
    refractionFbo_ = createFrameBuffer();
    refractionTextureId_ = createColorTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionDepthTextureId_ = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

GLuint WaterFrameBuffers::createFrameBuffer() {
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return fbo;
}

GLuint WaterFrameBuffers::createColorTextureAttachment(int width, int height) {
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
    if (checkErrors()) exit(EXIT_FAILURE);
    return texId;
}

GLuint WaterFrameBuffers::createDepthTextureAttachment(int width, int height) {
    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texId, 0);
    return texId;
}

GLuint WaterFrameBuffers::createDepthBufferAttachment(int width, int height) {
    GLuint buf;
    glGenRenderbuffers(1, &buf);
    glBindRenderbuffer(GL_RENDERBUFFER, buf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buf);
    return buf;
}
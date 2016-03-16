#include "water/water_frame_buffers.hpp"
#include "render_engine/display_manager.hpp"


namespace {
    constexpr int REFLECTION_WIDTH = 900, REFLECTION_HEIGHT = 675;
    constexpr int REFRACTION_WIDTH = 900, REFRACTION_HEIGHT = 675;
}

WaterFrameBuffers::WaterFrameBuffers() {
    initializeReflectionFrameBuffer();
    initializeRefractionFrameBuffer();
}

void WaterFrameBuffers::bindReflectionFrameBuffer() const {
    bindFrameBuffer(reflectionFbo_.get(), REFLECTION_WIDTH, REFLECTION_HEIGHT);
}

void WaterFrameBuffers::bindRefractionFrameBuffer() const {
    bindFrameBuffer(refractionFbo_.get(), REFRACTION_WIDTH, REFRACTION_HEIGHT);
}

void WaterFrameBuffers::unbindCurrentFrameBuffer() const {
    auto dimensions = DisplayManager::getWindow().getSize();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, dimensions.x, dimensions.y);
}

GLuint WaterFrameBuffers::getReflectionTexture() const {
    return reflectionTexture_.get();
}

GLuint WaterFrameBuffers::getRefractionTexture() const {
    return refractionTexture_.get();
}

GLuint WaterFrameBuffers::getRefractionDepthTexture() const {
    return refractionDepthTexture_.get();
}

void WaterFrameBuffers::bindFrameBuffer(GLuint fbo, int width, int height) const {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glViewport(0, 0, width, height);
}

void WaterFrameBuffers::initializeReflectionFrameBuffer() {
    reflectionFbo_ = createFrameBuffer();
    reflectionTexture_ = createColorTextureAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionDepthBuffer_ = createDepthBufferAttachment(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

void WaterFrameBuffers::initializeRefractionFrameBuffer() {
    refractionFbo_ = createFrameBuffer();
    refractionTexture_ = createColorTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionDepthTexture_ = createDepthTextureAttachment(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    unbindCurrentFrameBuffer();
}

gl::FramebufferHandle WaterFrameBuffers::createFrameBuffer() {
    gl::FramebufferHandle fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo.get());
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    return fbo;
}

gl::TextureHandle WaterFrameBuffers::createColorTextureAttachment(int width, int height) {
    gl::TextureHandle tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex.get());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
        GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.get(), 0);
    return tex;
}

gl::TextureHandle WaterFrameBuffers::createDepthTextureAttachment(int width, int height) {
    gl::TextureHandle tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex.get());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tex.get(), 0);
    return tex;
}

gl::RenderbufferHandle WaterFrameBuffers::createDepthBufferAttachment(int width, int height) {
    gl::RenderbufferHandle buf;
    glGenRenderbuffers(1, &buf);
    glBindRenderbuffer(GL_RENDERBUFFER, buf.get());
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, buf.get());
    return buf;
}
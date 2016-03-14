#pragma once
#include "toolbox/gl_handles.hpp"
#include <GL/glew.h>

class WaterFrameBuffers {
public:
    WaterFrameBuffers();

    void bindReflectionFrameBuffer() const;
    void bindRefractionFrameBuffer() const;
    void unbindCurrentFrameBuffer() const;

    GLuint getReflectionTexture() const;
    GLuint getRefractionTexture() const;
    GLuint getRefractionDepthTexture() const;

private:
    void initializeReflectionFrameBuffer();
    void initializeRefractionFrameBuffer();
    void bindFrameBuffer(GLuint fbo, int width, int height) const;

    gl::FramebufferHandle  createFrameBuffer();
    gl::TextureHandle      createColorTextureAttachment(int width, int height);
    gl::TextureHandle      createDepthTextureAttachment(int width, int height);
    gl::RenderbufferHandle createDepthBufferAttachment(int width, int height);

    gl::FramebufferHandle  reflectionFbo_;
    gl::TextureHandle      reflectionTexture_;
    gl::RenderbufferHandle reflectionDepthBuffer_;

    gl::FramebufferHandle  refractionFbo_;
    gl::TextureHandle      refractionTexture_;
    gl::TextureHandle      refractionDepthTexture_;
};

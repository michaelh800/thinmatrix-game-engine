#pragma once
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

    GLuint createFrameBuffer();
    GLuint createColorTextureAttachment(int width, int height);
    GLuint createDepthTextureAttachment(int width, int height);
    GLuint createDepthBufferAttachment(int width, int height);

    GLuint reflectionFbo_;
    GLuint reflectionTextureId_;
    GLuint reflectionDepthBufferId_;

    GLuint refractionFbo_;
    GLuint refractionTextureId_;
    GLuint refractionDepthTextureId_;
};

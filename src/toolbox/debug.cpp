#include "debug.hpp"


std::string getOpenGLError(GLenum err) {
    switch (err) {
        case GL_INVALID_ENUM:
            return "invalid enum";
        case GL_INVALID_VALUE:
            return "invalid value";
        case GL_INVALID_OPERATION:
            return "invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "invalid framebuffer operation";
        case GL_OUT_OF_MEMORY:
            return "out of memory";
        default:
            return "unknown";
    }
}

int printOpenGLErrors(const char *file, int line) {
    GLenum glErr;
    int retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        std::cerr << "glError in file " << file << " @ line " << line << ": "
                  << getOpenGLError(glErr) << std::endl;
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

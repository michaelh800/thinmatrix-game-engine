#include "debug.hpp"

int printOglError(const char *file, int line) {
    /* Returns 1 if an OpenGL error occurred, 0 otherwise. */
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        std::cerr << "glError in file " << file << " @ line " << line << ": " << glErr << std::endl;
        retCode = 1;
        glErr = glGetError();
    }
    return retCode;
}

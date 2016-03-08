#include "render_engine/glew.hpp"
#include <cstdlib>
#include <cstdio>

Glew::Glew() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("[ERROR]: Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }
}

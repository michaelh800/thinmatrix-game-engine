#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>

std::string getOpenGLError(GLenum err);

int printOpenGLErrors(const char *file, int line);

/**
 * Prints all OpenGL errors that have occurred along with the file and line
 * number of the corresponding checkErrors() call.
 */
#define checkErrors() printOpenGLErrors(__FILE__, __LINE__)

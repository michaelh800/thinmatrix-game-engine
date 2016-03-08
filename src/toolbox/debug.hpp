#pragma once
#include <GL/glew.h>
#include <iostream>


int printOglError(const char *file, int line);

#define printOpenGLError() printOglError(__FILE__, __LINE__)

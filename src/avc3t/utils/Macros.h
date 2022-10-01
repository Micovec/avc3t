#pragma once

// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <iostream>
#include <signal.h>

#ifdef _MSC_VER
#define ASSERT(x)                                                                                                                                                                  \
    if (!(x))                                                                                                                                                                      \
    __debugbreak()
#else
#define ASSERT(x)                                                                                                                                                                  \
    if (!(x))                                                                                                                                                                      \
    raise(SIGTRAP)
#endif

#define GLCall(x)                                                                                                                                                                  \
    GLClearError();                                                                                                                                                                \
    x;                                                                                                                                                                             \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
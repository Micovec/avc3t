#pragma once

// #include <GL/glew.h>
#ifdef __EMSCRIPTEN__
#include <GL/gl.h>
#include <GLES3/gl3.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <emscripten.h>
#else
#include <glad/gl.h>
#endif
#include <GLFW/glfw3.h>

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
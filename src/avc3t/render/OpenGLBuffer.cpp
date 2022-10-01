#include "OpenGLBuffer.h"

namespace AVC3T {
    OpenGLBuffer::OpenGLBuffer(std::size_t width, std::size_t height) : m_BufferID(0), m_Width(width), m_Height(height) {}

    OpenGLBuffer::~OpenGLBuffer() {}
}
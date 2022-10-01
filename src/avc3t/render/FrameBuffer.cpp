#include "FrameBuffer.h"

#include "../utils/Macros.h"

namespace AVC3T {
    FrameBuffer::FrameBuffer(std::size_t width, std::size_t height) : OpenGLBuffer(width, height) {
        GLCall(glGenFramebuffers(1, &m_BufferID));
    }

    FrameBuffer::FrameBuffer(FrameBuffer&& other) : OpenGLBuffer(other.m_Width, other.m_Height) {
        m_BufferID       = other.m_BufferID;
        other.m_BufferID = other.m_Width = other.m_Height = 0;
    }

    FrameBuffer::~FrameBuffer() {
        GLCall(glDeleteFramebuffers(1, &m_BufferID));
    }

    void FrameBuffer::Bind() const {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
    }

    void FrameBuffer::Unbind() const {
        GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
}
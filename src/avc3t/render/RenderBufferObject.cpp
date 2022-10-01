#include "RenderBufferObject.h"

#include "../utils/Macros.h"

namespace AVC3T {
    RenderBufferObject::RenderBufferObject(std::size_t width, std::size_t height) : OpenGLBuffer(width, height) {
        GLCall(glGenRenderbuffers(1, &m_BufferID));
        Bind();
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height)); // use a single renderbuffer object for both a depth AND stencil buffer.
        GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_BufferID)); // now actually attach it
        Unbind();
    }

    RenderBufferObject::~RenderBufferObject() {
        GLCall(glDeleteRenderbuffers(1, &m_BufferID));
    }

    void RenderBufferObject::Bind() const {
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_BufferID));
    }

    void RenderBufferObject::Unbind() const {
        GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    }
}
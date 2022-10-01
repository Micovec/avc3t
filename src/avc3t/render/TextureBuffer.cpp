#include "TextureBuffer.h"

#include "../utils/Macros.h"

namespace AVC3T {
    TextureBuffer::TextureBuffer(std::size_t width, std::size_t height) : OpenGLBuffer(width, height) {
        GLCall(glGenTextures(1, &m_BufferID));
        Bind();
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BufferID, 0));
        Unbind();
    }

    TextureBuffer::~TextureBuffer() {
        GLCall(glDeleteTextures(1, &m_BufferID));
    }

    void TextureBuffer::Bind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, m_BufferID));
    }

    void TextureBuffer::Unbind() const {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}
#include "FrameBufferObject.h"

namespace AVC3T {
    FrameBufferObject::FrameBufferObject(std::size_t width, std::size_t height) : m_FrameBuffer(nullptr), m_TextureBuffer(nullptr), m_RenderBufferObject(nullptr) {
        m_FrameBuffer = std::make_shared<FrameBuffer>(width, height);
        m_FrameBuffer->Bind();

        m_TextureBuffer = std::make_shared<TextureBuffer>(width, height);
        m_TextureBuffer->Bind();

        m_RenderBufferObject = std::make_shared<RenderBufferObject>(width, height);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        Unbind();
    }

    FrameBufferObject::FrameBufferObject(FrameBufferObject&& other) :
        m_FrameBuffer(other.m_FrameBuffer), m_TextureBuffer(other.m_TextureBuffer), m_RenderBufferObject(other.m_RenderBufferObject) {
        other.m_FrameBuffer.reset();
        other.m_TextureBuffer.reset();
        other.m_RenderBufferObject.reset();
    }

    void FrameBufferObject::Bind() const {
        GLCall(glViewport(0, 0, m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight()));
        m_FrameBuffer->Bind();
        m_TextureBuffer->Bind();
        m_RenderBufferObject->Bind();
    }

    void FrameBufferObject::Unbind() const {
        m_FrameBuffer->Unbind();
        m_TextureBuffer->Unbind();
        m_RenderBufferObject->Unbind();
    }
}
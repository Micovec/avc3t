#include "VertexBuffer.h"

#include "../utils/Macros.h"

namespace AVC3T {
    VertexBuffer::VertexBuffer(unsigned int size) : m_Size(size), m_Offset(0) {
        GLCall(glGenBuffers(1, &m_RendererID));
        Bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW));
    }

    VertexBuffer::VertexBuffer(const VertexBuffer& other) : m_Size(other.m_Size), m_Offset(other.m_Offset) {
        GLCall(glGenBuffers(1, &m_RendererID));
        Bind();
        GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, nullptr, GL_STATIC_DRAW));

        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID));
        GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_Size));
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& other) : m_RendererID(other.m_RendererID) {
        other.m_RendererID = 0;
    }

    VertexBuffer::~VertexBuffer() {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void VertexBuffer::AddData(const void* data, unsigned int size) {
        Bind();
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, m_Offset, size, data));
        m_Offset += size;
    }

    void VertexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void VertexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
}
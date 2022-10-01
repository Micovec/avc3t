#include "IndexBuffer.h"

#include "../utils/Macros.h"

namespace AVC3T {
    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_RendererID(0), m_Count(count) {
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    IndexBuffer::IndexBuffer(const IndexBuffer& other) : m_RendererID(0), m_Count(other.m_Count) {
        GLCall(glGenBuffers(1, &m_RendererID));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), nullptr, GL_STATIC_DRAW));

        GLCall(glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID));
        GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID));
        GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_Count * sizeof(unsigned int)));
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& other) : m_RendererID(other.m_RendererID), m_Count(other.m_Count) {
        other.m_RendererID = 0;
        other.m_Count      = 0;
    }

    IndexBuffer::~IndexBuffer() {
        GLCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void IndexBuffer::Unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
}
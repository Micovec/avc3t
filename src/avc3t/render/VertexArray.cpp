#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "../utils/Macros.h"

namespace AVC3T {
    VertexArray::VertexArray() : m_RendererID(0), m_VertexBuffer(), m_VertexBufferLayout(), m_VertexCount(0) {
        GLCall(glGenVertexArrays(1, &m_RendererID));
    }

    VertexArray::VertexArray(const VertexArray& other) : m_RendererID(0), m_VertexBuffer(), m_VertexBufferLayout(), m_VertexCount(0) {
        GLCall(glGenVertexArrays(1, &m_RendererID));

        std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(*other.m_VertexBuffer);
        SetBuffer(vb, other.m_VertexBufferLayout, other.m_VertexCount);
    }

    VertexArray::VertexArray(VertexArray&& other) :
        m_RendererID(other.m_RendererID), m_VertexBuffer(other.m_VertexBuffer), m_VertexBufferLayout(other.m_VertexBufferLayout), m_VertexCount(other.m_VertexCount) {
        other.m_RendererID = 0;
    }

    VertexArray::~VertexArray() {
        GLCall(glDeleteVertexArrays(1, &m_RendererID));
    }

    void VertexArray::SetBuffer(const std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout, size_t vertexCount) {
        m_VertexBuffer       = vb;
        m_VertexBufferLayout = layout;
        m_VertexCount        = vertexCount;

        Bind();
        vb->Bind();

        const auto&  elements = layout.GetElements();
        unsigned int offset   = 0;
        for (std::size_t i = 0; i < elements.size(); ++i) {
            const auto& element = elements[i];
            GLCall(glEnableVertexAttribArray(static_cast<GLuint>(i)));
            GLCall(glVertexAttribPointer(static_cast<GLuint>(i), element.count, element.type, element.normalized, 0, (GLvoid*)(offset)));
            offset += element.size * element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }

    void VertexArray::Bind() const {
        GLCall(glBindVertexArray(m_RendererID));
    }

    void VertexArray::Unbind() const {
        GLCall(glBindVertexArray(0));
    }
}
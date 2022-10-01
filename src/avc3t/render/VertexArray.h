#pragma once

#include <memory>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace AVC3T {
    class VertexBufferLayout;

    class VertexArray {
      public:
        VertexArray();
        VertexArray(const VertexArray& other);
        VertexArray(VertexArray&& other);
        ~VertexArray();

        void                          SetBuffer(const std::shared_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout, size_t vertexCount);

        std::shared_ptr<VertexBuffer> GetVertexBuffer() const {
            return m_VertexBuffer;
        }
        const VertexBufferLayout& GetVertexBufferLayout() const {
            return m_VertexBufferLayout;
        }

        void   Bind() const;
        void   Unbind() const;

        size_t GetVertexCount() const {
            return m_VertexCount;
        }

      private:
        unsigned int                  m_RendererID;

        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        VertexBufferLayout            m_VertexBufferLayout;
        size_t                        m_VertexCount;
    };
} // namespace AVC3T
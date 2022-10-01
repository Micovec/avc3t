#pragma once

namespace AVC3T {
    class VertexBuffer {
      public:
        VertexBuffer(unsigned int size);
        VertexBuffer(const VertexBuffer& other);
        VertexBuffer(VertexBuffer&& other);
        ~VertexBuffer();

        void         AddData(const void* data, unsigned int size);

        unsigned int GetSize() const {
            return m_Size;
        }

        void Bind() const;
        void Unbind() const;

      private:
        unsigned int m_Size;
        unsigned int m_RendererID;
        unsigned int m_Offset;
    };
}
#pragma once

namespace AVC3T {
    class IndexBuffer {
      public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        IndexBuffer(IndexBuffer&& other);
        IndexBuffer(const IndexBuffer& other);

        ~IndexBuffer();

        void                Bind() const;
        void                Unbind() const;

        inline unsigned int GetCount() const {
            return m_Count;
        }

      private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    };
}
#pragma once

#include "../utils/Macros.h"
#include <vector>

namespace AVC3T {
    struct VertexBufferElement {
        unsigned int        type;
        unsigned int        count;
        unsigned int        size;
        unsigned char       normalized;

        static unsigned int GetSizeOfType(unsigned int type) {
            switch (type) {
                case GL_FLOAT: return 4;
                case GL_UNSIGNED_INT: return 4;
                case GL_UNSIGNED_BYTE: return 1;
            }
            ASSERT(false);
            return 0;
        }
    };

    class VertexBufferLayout {
      public:
        VertexBufferLayout() : m_Elements() {}

        void PushFloat(unsigned int count, unsigned int size) {
            // TODO: ERROR fix this
            // static_assert(false);
            m_Elements.push_back({GL_FLOAT, count, size, GL_FALSE});
        }

        void Push(const VertexBufferElement& element) {
            m_Elements.push_back(element);
        }

        inline const std::vector<VertexBufferElement>& GetElements() const {
            return m_Elements;
        }

      private:
        std::vector<VertexBufferElement> m_Elements;
    };

    // template <>
    // void VertexBufferLayout::Push<float>(unsigned int count, unsigned int size) {
    //   m_Elements.push_back({GL_FLOAT, count, size, GL_FALSE});
    // }

    // template <>
    // void VertexBufferLayout::Push<unsigned int>(unsigned int count,
    //                                             unsigned int size) {
    //   m_Elements.push_back({GL_UNSIGNED_INT, count, size, GL_FALSE});
    // }

    // template <>
    // void VertexBufferLayout::Push<unsigned char>(unsigned int count,
    //                                              unsigned int size) {
    //   m_Elements.push_back({GL_UNSIGNED_BYTE, count, size, GL_TRUE});
    // }
} // namespace AVC3T
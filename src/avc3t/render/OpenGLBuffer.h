#pragma once

#include <cstddef>

#include "../utils/Macros.h"

namespace AVC3T {
    class OpenGLBuffer {
      public:
        OpenGLBuffer(std::size_t with, std::size_t height);
        OpenGLBuffer(const OpenGLBuffer& other) = delete;

        virtual ~OpenGLBuffer();

        virtual void Bind() const   = 0;
        virtual void Unbind() const = 0;

        unsigned int GetBufferID() const {
            return m_BufferID;
        }

        std::size_t GetWidth() const {
            return m_Width;
        }
        std::size_t GetHeight() const {
            return m_Height;
        }

      protected:
        unsigned int m_BufferID;

        std::size_t  m_Width, m_Height;
    };
}
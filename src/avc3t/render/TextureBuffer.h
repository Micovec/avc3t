#pragma once

#include "OpenGLBuffer.h"

namespace AVC3T {
    class TextureBuffer : public OpenGLBuffer {
      public:
        TextureBuffer(std::size_t width, std::size_t height);
        TextureBuffer(const TextureBuffer& other) = delete;
        TextureBuffer(TextureBuffer&& other)      = default;

        ~TextureBuffer();

        void Bind() const override;
        void Unbind() const override;
    };
}
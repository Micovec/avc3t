#pragma once

#include "OpenGLBuffer.h"
#include "TextureBuffer.h"
#include "RenderBufferObject.h"

namespace AVC3T {
    class FrameBuffer : public OpenGLBuffer {
      public:
        FrameBuffer(std::size_t width, std::size_t height);
        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer(FrameBuffer&& other);

        ~FrameBuffer();

        void Bind() const override;
        void Unbind() const override;
    };
}
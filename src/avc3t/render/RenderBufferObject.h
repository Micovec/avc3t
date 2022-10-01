#pragma once

#include "OpenGLBuffer.h"

namespace AVC3T {
    class RenderBufferObject : public OpenGLBuffer {
      public:
        RenderBufferObject(std::size_t width, std::size_t height);
        RenderBufferObject(const RenderBufferObject& other) = delete;
        RenderBufferObject(RenderBufferObject&& other)      = default;

        ~RenderBufferObject();

        void Bind() const override;
        void Unbind() const override;
    };
}
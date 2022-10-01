#pragma once

#include <memory>

#include "FrameBuffer.h"
#include "RenderBufferObject.h"
#include "TextureBuffer.h"

namespace AVC3T {
    class FrameBufferObject {
      public:
        FrameBufferObject(std::size_t width, std::size_t height);
        FrameBufferObject(const FrameBufferObject& other) = delete;
        FrameBufferObject(FrameBufferObject&& other);

        void         Bind() const;
        void         Unbind() const;

        unsigned int GetTextureID() const {
            return m_TextureBuffer->GetBufferID();
        }

        std::size_t GetWidth() {
            return m_FrameBuffer->GetWidth();
        }
        std::size_t GetHeight() {
            return m_FrameBuffer->GetHeight();
        }

      private:
        std::shared_ptr<FrameBuffer>        m_FrameBuffer;
        std::shared_ptr<TextureBuffer>      m_TextureBuffer;
        std::shared_ptr<RenderBufferObject> m_RenderBufferObject;
    };
} // namespace AVC3T
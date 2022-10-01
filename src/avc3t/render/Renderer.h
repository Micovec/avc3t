#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace AVC3T {
    class Renderer {
      public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib) const;
        void DrawLines(const VertexArray& va) const;
    };
}
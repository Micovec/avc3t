#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"

#include "../utils/Macros.h"

namespace AVC3T {
    void Renderer::Clear() const {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }

    void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib) const {
        va.Bind();
        ib.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::DrawLines(const VertexArray& va) const {
        va.Bind();
        GLCall(glDrawArrays(GL_LINES, 0, va.GetVertexCount()));
    }
}
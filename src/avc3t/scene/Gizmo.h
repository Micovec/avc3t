#pragma once

#include "SceneObject.h"

namespace AVC3T {
    struct Gizmo : public SceneObject {
        Gizmo() : SceneObject(GetNewMesh()) {}

      private:
        static inline std::shared_ptr<AVC3T::Mesh> GetNewMesh() {
            return std::make_shared<AVC3T::Mesh>(GetNewVertexArray());
        }

        static inline std::shared_ptr<VertexArray> GetNewVertexArray() {
            constexpr float               positions[] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1};

            constexpr float               colors[] = {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1};

            std::shared_ptr<VertexArray>  vertexArray = std::make_shared<AVC3T::VertexArray>();
            std::shared_ptr<VertexBuffer> vb          = std::make_shared<VertexBuffer>(3 * (6 + 6) * sizeof(float));
            vb->AddData(positions, 3 * 6 * sizeof(float));
            vb->AddData(colors, 3 * 6 * sizeof(float));

            VertexBufferLayout layout;
            layout.PushFloat(3, 6);
            layout.PushFloat(3, 6);
            vertexArray->SetBuffer(vb, layout, 6);

            return vertexArray;
        }
    };
} // namespace AVC3T
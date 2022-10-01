#pragma once

#include "SceneObject.h"

namespace AVC3T {
    struct WiredCube : public SceneObject {
        WiredCube(const glm::vec3& color = glm::vec3(0, 0, 0)) : SceneObject(GetNewMesh(color)) {}

      private:
        static inline std::shared_ptr<AVC3T::Mesh> GetNewMesh(const glm::vec3& color) {
            std::shared_ptr<AVC3T::Mesh> mesh = std::make_shared<AVC3T::Mesh>(GetNewVertexArray(color));
            mesh->SetMeshRendering(MeshRendering_Lines);
            return mesh;
        }

        static inline std::shared_ptr<VertexArray> GetNewVertexArray(const glm::vec3& color) {
            constexpr float positions[] = {
                // Bottom
                -1,
                -1,
                1,
                1,
                -1,
                1,
                1,
                -1,
                1,
                1,
                -1,
                -1,
                1,
                -1,
                -1,
                -1,
                -1,
                -1,
                -1,
                -1,
                -1,
                -1,
                -1,
                1,

                // Top
                -1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                1,
                -1,
                1,
                1,
                -1,
                -1,
                1,
                -1,
                -1,
                1,
                -1,
                -1,
                1,
                1,

                // Sides
                -1,
                -1,
                1,
                -1,
                1,
                1,
                1,
                -1,
                1,
                1,
                1,
                1,
                1,
                -1,
                -1,
                1,
                1,
                -1,
                -1,
                -1,
                -1,
                -1,
                1,
                -1,
            };
            constexpr size_t   vertexCount = 8 * 3;

            std::vector<float> colors(12 * 3 * 3);

            for (size_t i = 0; i < colors.size(); i += 3) {
                colors[i]     = color.x;
                colors[i + 1] = color.y;
                colors[i + 2] = color.z;
            }

            std::shared_ptr<VertexArray>  vertexArray = std::make_shared<AVC3T::VertexArray>();
            std::shared_ptr<VertexBuffer> vb          = std::make_shared<VertexBuffer>(colors.size() * sizeof(float) + sizeof(positions));
            vb->AddData(positions, sizeof(positions));
            vb->AddData(colors.data(), colors.size() * sizeof(float));

            VertexBufferLayout layout;
            layout.PushFloat(3, vertexCount);
            layout.PushFloat(3, vertexCount);
            vertexArray->SetBuffer(vb, layout, vertexCount);

            return vertexArray;
        }
    };
} // namespace AVC3T
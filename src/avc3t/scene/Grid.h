#pragma once

#include "SceneObject.h"

namespace AVC3T {
    struct Grid : public SceneObject {
        Grid() : SceneObject(GetNewMesh()) {}

      private:
        static inline std::shared_ptr<AVC3T::Mesh> GetNewMesh() {
            return std::make_shared<AVC3T::Mesh>(GetNewVertexArray());
        }

        static inline std::shared_ptr<VertexArray> GetNewVertexArray() {
            unsigned int       vertexCount = 0;
            std::vector<float> positions;
            std::vector<float> colors;

            const int          lineCountHalf = s_LineCount / 2;

            for (int x = -lineCountHalf; x <= lineCountHalf; ++x, vertexCount += 2) {
                positions.push_back(x);
                positions.push_back(0);
                positions.push_back(-lineCountHalf);

                positions.push_back(x);
                positions.push_back(0);
                positions.push_back(lineCountHalf);

                colors.push_back(0.357f);
                colors.push_back(0.357f);
                colors.push_back(0.357f);

                colors.push_back(0.357f);
                colors.push_back(0.357f);
                colors.push_back(0.357f);
            }

            for (int z = -lineCountHalf; z <= lineCountHalf; ++z, vertexCount += 2) {
                positions.push_back(-lineCountHalf);
                positions.push_back(0);
                positions.push_back(z);

                positions.push_back(lineCountHalf);
                positions.push_back(0);
                positions.push_back(z);

                colors.push_back(0.357f);
                colors.push_back(0.357f);
                colors.push_back(0.357f);

                colors.push_back(0.357f);
                colors.push_back(0.357f);
                colors.push_back(0.357f);
            }

            std::shared_ptr<VertexArray>  vertexArray = std::make_shared<AVC3T::VertexArray>();
            std::shared_ptr<VertexBuffer> vb          = std::make_shared<VertexBuffer>(static_cast<unsigned int>((positions.size() + colors.size())) * sizeof(float));
            vb->AddData(positions.data(), static_cast<unsigned int>(positions.size()) * sizeof(float));
            vb->AddData(colors.data(), static_cast<unsigned int>(colors.size()) * sizeof(float));

            VertexBufferLayout layout;
            layout.PushFloat(3, vertexCount);
            layout.PushFloat(3, vertexCount);
            vertexArray->SetBuffer(vb, layout, vertexCount);

            return vertexArray;
        }

      private:
        constexpr static int s_LineCount = 11;
    };
} // namespace AVC3T
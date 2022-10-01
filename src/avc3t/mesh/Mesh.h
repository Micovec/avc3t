#pragma once

#include "Material.h"

#include "../library/ShaderLibrary.h"

#include "../render/IndexBuffer.h"
#include "../render/VertexArray.h"

namespace AVC3T {
    enum MeshRendering {
        MeshRendering_Triangles,
        MeshRendering_Lines
    };

    class Mesh {
      public:
        Mesh();
        Mesh(const std::shared_ptr<VertexArray>& vArray, const std::shared_ptr<IndexBuffer>& iBuffer = nullptr,
             const Material& material = Material(glm::vec3(0), glm::vec3(0), nullptr));
        Mesh(const Mesh& other);
        Mesh(Mesh&& other);

        std::shared_ptr<VertexArray> GetVertexArray() const {
            return m_VertexArray;
        }
        std::shared_ptr<IndexBuffer> GetIndexBuffer() const {
            return m_IndexBuffer;
        }

        std::shared_ptr<Shader> GetShader() const {
            return m_Shader;
        }
        MeshRendering GetMeshRendering() const {
            return m_MeshRendering;
        }

        const Material& GetMaterial() const {
            return m_Material;
        }

        void SetMeshRendering(MeshRendering meshRendering) {
            m_MeshRendering = meshRendering;
        }

      private:
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;

        std::shared_ptr<Shader>      m_Shader;
        MeshRendering                m_MeshRendering;

        Material                     m_Material;
    };
}
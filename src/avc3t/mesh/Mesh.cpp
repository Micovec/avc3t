#include "Mesh.h"

#include <utility>

namespace AVC3T {
    Mesh::Mesh() : m_VertexArray(nullptr), m_IndexBuffer(nullptr), m_Shader(nullptr), m_MeshRendering(MeshRendering_Triangles), m_Material(glm::vec3(1), glm::vec3(1), nullptr) {}

    Mesh::Mesh(const std::shared_ptr<VertexArray>& vArray, const std::shared_ptr<IndexBuffer>& iBuffer, const Material& material) :
        m_VertexArray(vArray), m_IndexBuffer(iBuffer), m_Shader(ShaderLibrary::GetShader(SHADER_DEFAULT_NAME)), m_MeshRendering(MeshRendering_Triangles), m_Material(material) {}

    Mesh::Mesh(const Mesh& other) :
        m_VertexArray(std::make_shared<VertexArray>(*other.m_VertexArray)), m_IndexBuffer(std::make_shared<IndexBuffer>(*other.m_IndexBuffer)), m_Shader(other.m_Shader),
        m_MeshRendering(other.m_MeshRendering), m_Material(other.m_Material) {}

    Mesh::Mesh(Mesh&& other) :
        m_VertexArray(other.m_VertexArray), m_IndexBuffer(other.m_IndexBuffer), m_Shader(other.m_Shader), m_MeshRendering(other.m_MeshRendering), m_Material(other.m_Material) {}
}
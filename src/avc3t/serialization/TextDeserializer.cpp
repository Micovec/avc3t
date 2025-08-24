#include "TextDeserializer.h"

#include "../utils/StringUtils.h"
#include "SerDerConstants.h"
#include <stdexcept>

#define DESERIALIZE_NODE_IF_TYPE(type, node, stream)                                                                                                                               \
    if (type* castedNode = dynamic_cast<type*>(node)) {                                                                                                                            \
        DeserializeNode_##type(*castedNode, stream);                                                                                                                               \
        return;                                                                                                                                                                    \
    }

namespace AVC3T {
    void TextDeserializer::Deserialize(const Workspace& workspace, std::ostream& stream) {
        for (const auto& [_, elements] : workspace.GetElements()) {
            for (const auto& element : elements) {
                DeserializeElement(element, stream);
            }
        }
    }

    void TextDeserializer::DeserializeElement(const std::shared_ptr<WorkspaceElement>& element, std::ostream& stream) {
        WorkspaceElement* elementPtr = element.get();
        if (dynamic_cast<WorkspaceLink*>(elementPtr))
            return;

        // Values
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Value, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfScaleValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfTranslValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Value, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Value, elementPtr, stream);

        // Operator
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatAdd, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatDivide, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultiply, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultMat4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultVec3, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultVec4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatPower, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatSubstract, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Add, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Mult, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4MultVec4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Substract, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatMult, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Add, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Dot, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Multiply, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Substract, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Add, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Dot, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Multiply, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Substract, elementPtr, stream);

        // Transformations
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfLookAt, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationVector, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationX, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationY, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationZ, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfScale, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfTransl, elementPtr, stream);

        // Functions
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeAbs, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeAcos, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeAsin, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCeil, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeClamp, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCos, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMix, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloor, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMod, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeSign, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeSin, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Decompose, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Determinant, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Inverse, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Transpose, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatConjugate, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatInverse, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatLength, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatLerp, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatNormalize, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatSlerp, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatVec3Quat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Length, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Mix, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Normalize, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Mix, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Normalize, elementPtr, stream);

        // Conversions
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToMat4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToVec3, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToVec4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToFloat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToVec4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvAngleAxisToQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvEulerToQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToAngleAxis, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToEuler, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToFloat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToMat4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3Vec3ToQuat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3FloatToVec4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3ToFloat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToFloat, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToMat4, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToVec3Float, elementPtr, stream);

        // Projections
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjFrustum, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjOrtho, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjPerspective, elementPtr, stream);

        // Logical
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolAnd, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolNot, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolOr, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolValue, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolXor, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpEqual, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpNotEqual, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpSmaller, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpSmallerEqual, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodePick, elementPtr, stream);

        // Object
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeEmbeddedObject, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeExternalObject, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeSceneObject, elementPtr, stream);

        // Miscellaneous
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeCamera, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeText, elementPtr, stream);
        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeTime, elementPtr, stream);

        std::string message = "Could not deserialize node: '";
        message += typeid(element).name();
        message += "'. Not implemented.";

        throw std::runtime_error(message);
    }

    void TextDeserializer::DeserializeNode(const char* name, WorkspaceNode& node, bool deserializeValues, std::ostream& stream) {
        DeserializeNodeName(name, stream);
        DeserializeNodeProperties(node, deserializeValues, stream);
    }

    void TextDeserializer::DeserializeNodeName(const char* name, std::ostream& stream) {
        stream << m_Tabs << name << SERDER_COLUMN << std::endl;
    }

    void TextDeserializer::DeserializeNodeProperties(WorkspaceNode& node, bool deserializeValues, std::ostream& stream) {
        m_Tabs++;

        stream << m_Tabs << SERDER_ID << node.GetId() << std::endl;
        stream << m_Tabs << SERDER_POSITION << node.GetPosition().x << SERDER_VALUE_SEPARATOR << node.GetPosition().y << std::endl;
        stream << m_Tabs << SERDER_DESCRIPTION << node.GetTitle() << std::endl;

        DeserializeOutputs(node.GetOutputPins(), deserializeValues, stream);

        m_Tabs--;
    }

    void TextDeserializer::DeserializeOutputs(std::vector<std::shared_ptr<WorkspaceOutputPin>>& outputs, bool deserializeValues, std::ostream& stream) {
        stream << m_Tabs << SERDER_OUTPUTS << std::endl;
        m_Tabs++;

        for (std::size_t outputIndex = 0; outputIndex < outputs.size(); ++outputIndex) {
            auto& output = outputs[outputIndex];
            stream << m_Tabs << SERDER_OUTPUT << std::endl;
            m_Tabs++;

            if (deserializeValues)
                DeserializeIOValue(output->Output.Type, output->Output.Value, stream);

            stream << m_Tabs << SERDER_CONNECTIONS << std::endl;
            m_Tabs++;

            stream << m_Tabs << SERDER_COUNT << output->Links.size() << std::endl;

            for (auto&& link : output->Links) {
                stream << m_Tabs << SERDER_CONNECTION << std::endl;
                m_Tabs++;

                auto& inputs = link->InputPin.Node->GetInputPins();
                for (std::size_t inputIndex = 0; inputIndex < inputs.size(); ++inputIndex) {
                    if (inputs[inputIndex]->Link == link) {
                        stream << m_Tabs << SERDER_ID << link->InputPin.Node->GetId() << std::endl;
                        stream << m_Tabs << SERDER_INPUT_INDEX << inputIndex << std::endl;
                        break;
                    }
                }

                m_Tabs--;
            }

            m_Tabs -= 2;
        }

        m_Tabs--;
    }

    void TextDeserializer::DeserializeIOValue(const WorkspaceIOType& type, const WorkspaceIOValue& value, std::ostream& stream) {
        stream << m_Tabs << SERDER_VALUE;

        switch (type) {
            case WorkspaceIOType_Bool: stream << *value.b << std::endl; break;

            case WorkspaceIOType_Float: stream << *value.f << std::endl; break;

            case WorkspaceIOType_Vec3:
                stream << value.vec3->x << SERDER_VALUE_SEPARATOR;
                stream << value.vec3->y << SERDER_VALUE_SEPARATOR;
                stream << value.vec3->z << std::endl;
                break;

            case WorkspaceIOType_Vec4:
                stream << value.vec4->x << SERDER_VALUE_SEPARATOR;
                stream << value.vec4->y << SERDER_VALUE_SEPARATOR;
                stream << value.vec4->z << SERDER_VALUE_SEPARATOR;
                stream << value.vec4->w << std::endl;
                break;

            case WorkspaceIOType_Mat4:
                for (int i = 0; i < 4; i++) {
                    stream << value.mat4->operator[](i).x << SERDER_VALUE_SEPARATOR;
                    stream << value.mat4->operator[](i).y << SERDER_VALUE_SEPARATOR;
                    stream << value.mat4->operator[](i).z << SERDER_VALUE_SEPARATOR;
                    stream << value.mat4->operator[](i).w;

                    if (i < 3)
                        stream << SERDER_VALUE_SEPARATOR;
                    else
                        stream << std::endl;
                }
                break;

            case WorkspaceIOType_Quat:
                stream << value.quat->x << SERDER_VALUE_SEPARATOR;
                stream << value.quat->y << SERDER_VALUE_SEPARATOR;
                stream << value.quat->z << SERDER_VALUE_SEPARATOR;
                stream << value.quat->w << std::endl;
                break;
        }
    }

    void TextDeserializer::DeserializeNode_WorkspaceNodeEmbeddedObject(WorkspaceNodeEmbeddedObject& node, std::ostream& stream) {
        DeserializeNodeName(SERDER_NODE_EMBEDDED_OBJECT, stream);

        m_Tabs = 1;

        stream << m_Tabs << SERDER_NAME << node.GetSceneObjectName() << std::endl;
        stream << m_Tabs << SERDER_MESH << std::endl;
        m_Tabs++;

        stream << m_Tabs << SERDER_VERTEX_ARRAY << std::endl;
        m_Tabs++;

        stream << m_Tabs << SERDER_VERTEX_BUFFER << std::endl;
        m_Tabs++;

        auto mesh        = node.GetSceneObject()->mesh;
        auto vertexArray = mesh->GetVertexArray();

        // Vertex buffer
        auto vertexBuffer = vertexArray->GetVertexBuffer();
        stream << m_Tabs << SERDER_SIZE << vertexBuffer->GetSize() << std::endl;
        stream << m_Tabs << SERDER_DATA << std::hex;

        unsigned int* data = new unsigned int[vertexBuffer->GetSize()];

        vertexArray->Bind();
        // GLCall(glGetBufferSubData(GL_ARRAY_BUFFER, 0, vertexBuffer->GetSize(), data));
        vertexArray->Unbind();

        for (unsigned int i = 0; i < vertexBuffer->GetSize(); ++i) {
            stream << data[i] << SERDER_VALUE_SEPARATOR;
        }
        stream << std::dec << std::endl;
        m_Tabs--;
        delete[] data;

        // Vertex buffer layout
        stream << m_Tabs << SERDER_VERTEX_BUFFER_LAYOUT << std::endl;
        m_Tabs++;

        stream << m_Tabs << SERDER_ELEMENTS << std::endl;
        m_Tabs++;

        const auto vertexBufferLayout = vertexArray->GetVertexBufferLayout();
        stream << m_Tabs << SERDER_SIZE << vertexBufferLayout.GetElements().size() << std::endl;

        for (const auto& element : vertexBufferLayout.GetElements()) {
            stream << m_Tabs << SERDER_ELEMENT << std::endl;
            m_Tabs++;

            stream << m_Tabs << SERDER_TYPE << element.type << std::endl;
            stream << m_Tabs << SERDER_COUNT << element.count << std::endl;
            stream << m_Tabs << SERDER_SIZE << element.size << std::endl;
            stream << m_Tabs << SERDER_NORMALIZED << static_cast<unsigned int>(element.normalized) << std::endl;
            m_Tabs--;
        }

        m_Tabs -= 2;

        // Vertex count
        stream << m_Tabs << SERDER_VERTEX_COUNT << vertexArray->GetVertexCount() << std::endl;
        m_Tabs--;

        // Index buffer
        stream << m_Tabs << SERDER_INDEX_BUFFER << std::endl;
        m_Tabs++;

        auto indexBuffer = mesh->GetIndexBuffer();
        stream << m_Tabs << SERDER_SIZE << indexBuffer->GetCount() << std::endl;
        stream << m_Tabs << SERDER_DATA << std::hex;

        data = new unsigned int[indexBuffer->GetCount()];
        indexBuffer->Bind();
        // GLCall(glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBuffer->GetCount() * sizeof(unsigned int), data));
        indexBuffer->Unbind();

        for (unsigned int i = 0; i < indexBuffer->GetCount(); ++i) {
            stream << data[i] << SERDER_VALUE_SEPARATOR;
        }
        delete[] data;

        stream << std::dec << std::endl;
        m_Tabs--;

        // Material
        const auto& material = mesh->GetMaterial();
        stream << m_Tabs << SERDER_MATERIAL << std::endl;
        m_Tabs++;

        glm::vec3 ambientColor = material.AmbientColor;
        stream << m_Tabs << SERDER_AMBIENT_COLOR << ambientColor.r << SERDER_VALUE_SEPARATOR << ambientColor.g << SERDER_VALUE_SEPARATOR << ambientColor.b << std::endl;
        stream << m_Tabs << SERDER_DIFFUSE_COLOR << ambientColor.r << SERDER_VALUE_SEPARATOR << ambientColor.g << SERDER_VALUE_SEPARATOR << ambientColor.b << std::endl;

        // Texture
        stream << m_Tabs << SERDER_TEXTURE << std::endl;
        m_Tabs++;

        auto texture = material.texture;
        stream << m_Tabs << SERDER_WIDTH << texture->GetWidth() << std::endl;
        stream << m_Tabs << SERDER_HEIGHT << texture->GetHeight() << std::endl;
        stream << m_Tabs << SERDER_COMPONENT_COUNT << texture->GetComponentCount() << std::endl;

        int            textureDataSize = texture->GetWidth() * texture->GetHeight() * texture->GetComponentCount();
        unsigned char* textureData     = new unsigned char[textureDataSize];
        texture->Bind();
        GLCall(glGetTexImage(GL_TEXTURE_2D, 0, Texture::GetFormatFromComponentCount(texture->GetComponentCount()), GL_UNSIGNED_BYTE, textureData));
        texture->Unbind();

        stream << m_Tabs << SERDER_DATA << std::hex;
        for (int i = 0; i < textureDataSize; ++i) {
            stream << +textureData[i] << SERDER_VALUE_SEPARATOR;
        }
        stream << std::dec << std::endl;
        delete[] textureData;

        m_Tabs = 0;

        DeserializeNodeProperties(node, false, stream);
    }

    void TextDeserializer::DeserializeNode_WorkspaceNodeExternalObject(WorkspaceNodeExternalObject& node, std::ostream& stream) {
        DeserializeNodeName(SERDER_NODE_EXTERNAL_OBJECT, stream);

        m_Tabs = 1;
        stream << m_Tabs << SERDER_PATH << node.GetPath() << std::endl;
        m_Tabs = 0;

        DeserializeNodeProperties(node, false, stream);
    }

    void TextDeserializer::DeserializeNode_WorkspaceNodeSceneObject(WorkspaceNodeSceneObject& node, std::ostream& stream) {
        DeserializeNodeName(SERDER_NODE_SCENE_OBJECT, stream);

        m_Tabs = 1;
        stream << m_Tabs << SERDER_NAME << node.GetSceneObjectName() << std::endl;
        m_Tabs = 0;

        DeserializeNodeProperties(node, false, stream);
    }

    void TextDeserializer::DeserializeNode_WorkspaceNodeCamera(WorkspaceNodeCamera& node, std::ostream& stream) {
        DeserializeNodeName(SERDER_NODE_CAMERA, stream);

        ImVec2 size = node.GetSize();

        m_Tabs = 1;
        stream << m_Tabs << SERDER_SIZE << size.x << SERDER_VALUE_SEPARATOR << size.y << std::endl;
        m_Tabs = 0;

        DeserializeNodeProperties(node, false, stream);
    }

    void TextDeserializer::DeserializeNode_WorkspaceNodeText(WorkspaceNodeText& node, std::ostream& stream) {
        DeserializeNodeName(SERDER_NODE_TEXT, stream);

        std::string text = node.GetText();
        StringUtils::ReplaceAll(text, "\n", "\\n");

        ImVec2 size = node.GetSize();

        m_Tabs = 1;
        stream << m_Tabs << SERDER_TEXT << text << std::endl;
        stream << m_Tabs << SERDER_SIZE << size.x << SERDER_VALUE_SEPARATOR << size.y << std::endl;
        m_Tabs = 0;

        DeserializeNodeProperties(node, false, stream);
    }
} // namespace AVC3T

#undef DESERIALIZE_NODE_IF_TYPE

#include "Serializer.h"

#include <map>
#include <stdexcept>

#include "../utils/BitUtils.h"
#include "../utils/StringUtils.h"
#include "SerDerConstants.h"

namespace AVC3T {
    void Serializer::Serialize(Workspace& workspace, Scene& scene, std::istream& stream) {
        stream >> std::noskipws;

        std::map<std::size_t, std::shared_ptr<WorkspaceNode>>                                 nodes;
        std::map<std::size_t, std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>> connections;

        while (stream.good()) {
            auto idNode = SerializeNode(connections, scene, stream);
            if (idNode.second == nullptr)
                break;

            nodes[idNode.first] = idNode.second;
            workspace.AddNode(idNode.second);
        }

        MakeConnections(workspace, nodes, connections);
    }

    void Serializer::MakeConnections(Workspace& workspace, std::map<std::size_t, std::shared_ptr<WorkspaceNode>>& nodes,
                                     std::map<std::size_t, std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>>& connections) {
        for (auto& [nodeID, node] : nodes) {
            auto& nodeOutputConnections = connections[nodeID];

            for (auto& connection : nodeOutputConnections) {
                std::size_t otherNodeID = std::get<0>(connection);
                std::size_t inputIndex  = std::get<1>(connection);
                std::size_t outputIndex = std::get<2>(connection);

                auto&       inputPin  = nodes[otherNodeID]->GetInputPins()[inputIndex];
                auto&       outputPin = node->GetOutputPins()[outputIndex];
                if (BitUtils::BitCount(outputPin->Output.Type) > 1)
                    outputPin->Output.Disabled = false;

                workspace.CreateLink(inputPin.get(), outputPin.get());
            }
        }
    }

    std::pair<std::size_t, std::shared_ptr<WorkspaceNode>>
    Serializer::SerializeNode(std::map<std::size_t, std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>>& connections, Scene& scene, std::istream& stream) {
        std::pair<std::shared_ptr<WorkspaceNode>, bool> nodePair = {nullptr, false};
        while (!nodePair.first) {
            nodePair = SerializeNodeType(scene, stream);

            if (stream.eof())
                return {-1, nullptr};
        }

        m_Tabs++;

        std::size_t id       = SerializeId(stream);
        ImVec2      position = SerializePosition(stream);
        std::string title    = SerializeTitle(stream);

        nodePair.first->SetPosition(position);
        nodePair.first->SetTitle(title);

        connections[id] = SerializeOutputConnections(*nodePair.first, nodePair.second, stream);

        m_Tabs--;

        return {id, nodePair.first};
    }

    std::pair<std::shared_ptr<WorkspaceNode>, bool> Serializer::SerializeNodeType(Scene& scene, std::istream& stream) {
        std::pair<std::shared_ptr<WorkspaceNode>, bool> nodePair = {nullptr, false};

        std::string                                     line;
        stream >> line;
        if (line.empty())
            return nodePair;

        m_StreamExpect.ExpectNewLine(stream);

        std::string nodeName = line.substr(0, line.find_last_of(':'));
        const char* name     = nodeName.data();

        // Values
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatValue, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Value, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Value, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Value, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatValue, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfTranslValue, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfScaleValue, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationValue, name, nodePair);

        // Operator
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatAdd, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatDivide, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultiply, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultMat4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultVec3, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMultVec4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatPower, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatSubstract, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Add, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Mult, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4MultVec4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Substract, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatMult, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Add, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Dot, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Multiply, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Substract, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Add, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Dot, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Multiply, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Substract, name, nodePair);

        // Transformations
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfLookAt, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationVector, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationX, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationY, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfRotationZ, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfScale, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTransfTransl, name, nodePair);

        // Functions
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeAbs, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeAcos, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeAsin, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCeil, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeClamp, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCos, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatMix, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloor, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMod, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeSign, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeSin, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Decompose, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Determinant, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Inverse, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeMat4Transpose, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatConjugate, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatInverse, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatLength, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatLerp, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatNormalize, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatSlerp, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeQuatVec3Quat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Length, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Mix, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec3Normalize, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Mix, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeVec4Normalize, name, nodePair);

        // Conversions
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToMat4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToVec3, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvFloatToVec4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToFloat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvMat4ToVec4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvAngleAxisToQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvEulerToQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToAngleAxis, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToEuler, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToFloat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvQuatToMat4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3Vec3ToQuat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3FloatToVec4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec3ToFloat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToFloat, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToMat4, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeConvVec4ToVec3Float, name, nodePair);

        // Projections
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjFrustum, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjOrtho, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeProjPerspective, name, nodePair);

        // Logical
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolAnd, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolNot, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolOr, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolValue, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeBoolXor, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpEqual, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpNotEqual, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpSmaller, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeCmpSmallerEqual, name, nodePair);
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodePick, name, nodePair);

        // Objects
        if (!std::strcmp(name, SERDER_NODE_EMBEDDED_OBJECT)) {
            m_Tabs++;
            auto node = SerializeNode_WorkspaceNodeEmbeddedObject(scene, stream);
            m_Tabs--;

            return {node, false};
        }
        if (!std::strcmp(name, SERDER_NODE_EXTERNAL_OBJECT)) {
            m_Tabs++;

            std::string objectPath;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_PATH) >> objectPath;
            m_StreamExpect.ExpectNewLine(stream);
            m_Tabs--;

            return {std::make_shared<WorkspaceNodeExternalObject>(scene, objectPath), false};
        }
        if (!std::strcmp(name, SERDER_NODE_SCENE_OBJECT)) {
            m_Tabs++;

            std::string sceneObjectName;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_NAME) >> sceneObjectName;
            m_StreamExpect.ExpectNewLine(stream);
            m_Tabs--;

            return {std::make_shared<WorkspaceNodeSceneObject>(scene, sceneObjectName), false};
        }

        // Miscellaneous
        if (!std::strcmp(name, SERDER_NODE_CAMERA)) {
            m_Tabs++;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE);

            ImVec2 size;
            stream >> size.x >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> size.y;

            m_StreamExpect.ExpectNewLine(stream);
            m_Tabs--;

            auto node = std::make_shared<WorkspaceNodeCamera>(scene);
            node->SetSize(size);

            return {node, false};
        }
        if (!std::strcmp(name, SERDER_NODE_TEXT)) {
            m_Tabs++;

            // Text
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_TEXT);

            std::string text;
            std::getline(stream, text);
            StringUtils::ReplaceAll(text, "\\n", "\n");

            // Size
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE);

            ImVec2 size;
            stream >> size.x >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> size.y;

            m_StreamExpect.ExpectNewLine(stream);
            m_Tabs--;

            auto node = std::make_shared<WorkspaceNodeText>(true);
            node->SetText(text);
            node->SetSize(size);

            return {node, false};
        }
        SERIALIZE_NODE_IF_TYPE(WorkspaceNodeTime, name, nodePair);

        std::string message = "Could not serialize '";
        message += name;
        message += "'. Not implemented.";

        throw std::runtime_error(message);
    }

    std::size_t Serializer::SerializeId(std::istream& stream) {
        std::size_t id;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_ID) >> id;
        m_StreamExpect.ExpectNewLine(stream);

        return id;
    }

    ImVec2 Serializer::SerializePosition(std::istream& stream) {
        ImVec2 position(0, 0);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_POSITION) >> position.x;
        stream >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> position.y;
        m_StreamExpect.ExpectNewLine(stream);

        return position;
    }

    std::string Serializer::SerializeTitle(std::istream& stream) {
        std::string title;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_DESCRIPTION);
        std::getline(stream, title);

        return title;
    }

    std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> Serializer::SerializeOutputConnections(WorkspaceNode& node, bool serializeValues, std::istream& stream) {
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_OUTPUTS);
        m_StreamExpect.ExpectNewLine(stream);

        m_Tabs++;

        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> connections;
        for (std::size_t outputIndex = 0; outputIndex < node.GetOutputPins().size(); ++outputIndex) {
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_OUTPUT);
            m_StreamExpect.ExpectNewLine(stream);

            m_Tabs++;

            if (serializeValues) {
                auto& output = node.GetOutputPins()[outputIndex];
                SerializeIOValue(output->Output.Type, output->Output.Value, stream);
            }

            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_CONNECTIONS);
            m_StreamExpect.ExpectNewLine(stream);

            m_Tabs++;

            std::size_t count;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_COUNT) >> count;
            m_StreamExpect.ExpectNewLine(stream);

            for (std::size_t k = 0; k < count; ++k) {
                stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_CONNECTION);
                m_StreamExpect.ExpectNewLine(stream);

                m_Tabs++;

                std::size_t otherNodeId;
                stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_ID) >> otherNodeId;
                m_StreamExpect.ExpectNewLine(stream);

                std::size_t inputIndex;
                stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_INPUT_INDEX) >> inputIndex;
                m_StreamExpect.ExpectNewLine(stream);

                connections.push_back({otherNodeId, inputIndex, outputIndex});

                m_Tabs--;
            }

            m_Tabs -= 2;
        }

        m_Tabs--;

        return connections;
    }

    void Serializer::SerializeIOValue(const WorkspaceIOType& type, const WorkspaceIOValue& value, std::istream& stream) {
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_VALUE);

        m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR);
        switch (type) {
            case WorkspaceIOType_Bool: stream >> *value.b; break;

            case WorkspaceIOType_Float: stream >> *value.f; break;

            case WorkspaceIOType_Vec3: stream >> value.vec3->x >> m_StreamExpect >> value.vec3->y >> m_StreamExpect >> value.vec3->z; break;

            case WorkspaceIOType_Vec4: stream >> value.vec4->x >> m_StreamExpect >> value.vec4->y >> m_StreamExpect >> value.vec4->z >> m_StreamExpect >> value.vec4->w; break;

            case WorkspaceIOType_Mat4:
                for (int i = 0; i < 4; ++i) {
                    stream >> value.mat4->operator[](i).x >> m_StreamExpect;
                    stream >> value.mat4->operator[](i).y >> m_StreamExpect;
                    stream >> value.mat4->operator[](i).z >> m_StreamExpect;
                    stream >> value.mat4->operator[](i).w;

                    if (i < 3)
                        stream >> m_StreamExpect;
                }

                break;

            case WorkspaceIOType_Quat: stream >> value.quat->x >> m_StreamExpect >> value.quat->y >> m_StreamExpect >> value.quat->z >> m_StreamExpect >> value.quat->w; break;

            default: break;
        }

        m_StreamExpect.ExpectNewLine(stream);
    }

    std::shared_ptr<WorkspaceNode> Serializer::SerializeNode_WorkspaceNodeEmbeddedObject(Scene& scene, std::istream& stream) {
        std::string objectName;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_NAME);
        std::getline(stream, objectName);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_MESH);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_VERTEX_ARRAY);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_VERTEX_BUFFER);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        unsigned int vertexBufferSize;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE) >> vertexBufferSize;
        m_StreamExpect.ExpectNewLine(stream);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_DATA);

        unsigned int* data = new unsigned int[vertexBufferSize];
        stream >> std::hex;

        for (unsigned int i = 0; i < vertexBufferSize; ++i) {
            stream >> data[i] >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR);
        }
        stream >> std::dec;
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs--;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_VERTEX_BUFFER_LAYOUT);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_ELEMENTS);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        std::size_t elementCount;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE) >> elementCount;
        m_StreamExpect.ExpectNewLine(stream);

        VertexBufferLayout layout;
        for (std::size_t i = 0; i < elementCount; ++i) {
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_ELEMENT);
            m_StreamExpect.ExpectNewLine(stream);
            m_Tabs++;

            unsigned int type;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_TYPE) >> type;
            m_StreamExpect.ExpectNewLine(stream);

            unsigned int count;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_COUNT) >> count;
            m_StreamExpect.ExpectNewLine(stream);

            unsigned int size;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE) >> size;
            m_StreamExpect.ExpectNewLine(stream);

            unsigned int normalized;
            stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_NORMALIZED) >> normalized;
            m_StreamExpect.ExpectNewLine(stream);

            layout.Push(VertexBufferElement{type, count, size, static_cast<unsigned char>(normalized)});

            m_Tabs--;
        }

        m_Tabs -= 2;

        std::size_t vertexCount;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_VERTEX_COUNT) >> vertexCount;
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs--;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_INDEX_BUFFER);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        unsigned int indexBufferSize;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_SIZE) >> indexBufferSize;
        m_StreamExpect.ExpectNewLine(stream);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_DATA);

        std::shared_ptr<VertexArray>  va = std::make_shared<VertexArray>();
        std::shared_ptr<VertexBuffer> vb = std::make_shared<VertexBuffer>(vertexBufferSize);

        vb->AddData(data, vertexBufferSize);
        va->SetBuffer(vb, layout, vertexCount);

        delete[] data;
        data = new unsigned int[indexBufferSize];

        stream >> std::hex;
        for (unsigned int i = 0; i < indexBufferSize; ++i) {
            stream >> data[i] >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR);
        }
        stream >> std::dec;
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs--;

        std::shared_ptr<IndexBuffer> ib = std::make_shared<IndexBuffer>(data, indexBufferSize);

        delete[] data;

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_MATERIAL);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        glm::vec3 ambientColor;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_AMBIENT_COLOR);
        stream >> ambientColor.r >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> ambientColor.g >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> ambientColor.b;
        m_StreamExpect.ExpectNewLine(stream);

        glm::vec3 diffuseColor;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_DIFFUSE_COLOR);
        stream >> diffuseColor.r >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> diffuseColor.g >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR) >> diffuseColor.b;
        m_StreamExpect.ExpectNewLine(stream);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_TEXTURE);
        m_StreamExpect.ExpectNewLine(stream);
        m_Tabs++;

        int textureWidth;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_WIDTH) >> textureWidth;
        m_StreamExpect.ExpectNewLine(stream);

        int textureHeight;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_HEIGHT) >> textureHeight;
        m_StreamExpect.ExpectNewLine(stream);

        int componentCount;
        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_COMPONENT_COUNT) >> componentCount;
        m_StreamExpect.ExpectNewLine(stream);

        stream >> m_Tabs >> m_StreamExpect.Expect(SERDER_DATA);

        int            textureDataSize = textureWidth * textureHeight * componentCount;
        unsigned char* textureData     = new unsigned char[textureDataSize];
        stream >> std::hex;

        for (int i = 0; i < textureDataSize; ++i) {
            unsigned int value;
            stream >> value >> m_StreamExpect.Expect(SERDER_VALUE_SEPARATOR);

            textureData[i] = static_cast<unsigned char>(value);
        }
        stream >> std::dec;
        m_StreamExpect.ExpectNewLine(stream);

        m_Tabs -= 3;

        auto texture = std::make_shared<Texture>(textureWidth, textureHeight, componentCount, textureData);
        auto mesh    = std::make_shared<Mesh>(va, ib, Material(ambientColor, diffuseColor, texture));
        auto object  = std::make_shared<SceneObject>(mesh);

        delete[] textureData;

        return std::make_shared<WorkspaceNodeEmbeddedObject>(scene, objectName, object);
    }
} // namespace AVC3T
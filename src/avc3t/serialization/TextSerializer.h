#pragma once

#include <istream>

#include "SerDerTab.h"
#include "StreamExpect.h"

#include "ISerializer.h"

#define SERIALIZE_NODE_DEF(type)                                                                                                                                                   \
    std::pair<std::shared_ptr<WorkspaceNode>, bool> SerializeNode_##type(std::shared_ptr<WorkspaceNode> node) {                                                                    \
        return {std::make_shared<type>(), false};                                                                                                                                  \
    }

#define SERIALIZE_NODE_VALUES_DEF(type)                                                                                                                                            \
    std::pair<std::shared_ptr<WorkspaceNode>, bool> SerializeNode_##type(std::shared_ptr<WorkspaceNode> node) {                                                                    \
        return {std::make_shared<type>(), true};                                                                                                                                   \
    }

#define SERIALIZE_NODE_IF_TYPE(type, name, nodePair)                                                                                                                               \
    if (!std::strcmp(#type, name)) {                                                                                                                                               \
        nodePair = SerializeNode_##type(nodePair.first);                                                                                                                           \
        return nodePair;                                                                                                                                                           \
    }

namespace AVC3T {
    class TextSerializer : public ISerializer {
      public:
        virtual ~TextSerializer() {}
        void Serialize(Workspace& workspace, Scene& scene, std::istream& stream) override;

      private:
        std::pair<std::size_t, std::shared_ptr<WorkspaceNode>> SerializeNode(std::map<std::size_t, std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>>& connections,
                                                                             Scene& scene, std::istream& stream);
        std::pair<std::shared_ptr<WorkspaceNode>, bool>        SerializeNodeType(Scene& scene, std::istream& stream);

        std::size_t                                            SerializeId(std::istream& stream);
        ImVec2                                                 SerializePosition(std::istream& stream);
        std::string                                            SerializeTitle(std::istream& stream);
        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> SerializeOutputConnections(WorkspaceNode& node, bool serializeValues, std::istream& stream);
        void                                                           SerializeIOValue(const WorkspaceIOType& type, const WorkspaceIOValue& value, std::istream& stream);

        void                                                           MakeConnections(Workspace& workspace, std::map<std::size_t, std::shared_ptr<WorkspaceNode>>& nodes,
                                                                                       std::map<std::size_t, std::vector<std::tuple<std::size_t, std::size_t, std::size_t>>>& connections);

        // Values
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeFloatValue)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeMat4Value)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeQuatValue)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfRotationValue)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfScaleValue)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfTranslValue)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeVec3Value)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeVec4Value)

        // Operator
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatAdd)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatDivide)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMultiply)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMultMat4)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMultQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMultVec3)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMultVec4)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatPower)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatSubstract)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Add)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Mult)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4MultVec4)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Substract)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatMult)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Add)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Dot)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Multiply)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Substract)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Add)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Dot)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Multiply)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Substract)

        // Transformation
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfLookAt)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationVector)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationX)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationY)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationZ)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfScale)
        SERIALIZE_NODE_DEF(WorkspaceNodeTransfTransl)

        // Functions
        SERIALIZE_NODE_DEF(WorkspaceNodeAbs)
        SERIALIZE_NODE_DEF(WorkspaceNodeAcos)
        SERIALIZE_NODE_DEF(WorkspaceNodeAsin)
        SERIALIZE_NODE_DEF(WorkspaceNodeCeil)
        SERIALIZE_NODE_DEF(WorkspaceNodeClamp)
        SERIALIZE_NODE_DEF(WorkspaceNodeCos)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloatMix)
        SERIALIZE_NODE_DEF(WorkspaceNodeFloor)
        SERIALIZE_NODE_DEF(WorkspaceNodeMod)
        SERIALIZE_NODE_DEF(WorkspaceNodeSign)
        SERIALIZE_NODE_DEF(WorkspaceNodeSin)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Decompose)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Determinant)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Inverse)
        SERIALIZE_NODE_DEF(WorkspaceNodeMat4Transpose)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatConjugate)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatInverse)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatLength)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatLerp)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatNormalize)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatSlerp)
        SERIALIZE_NODE_DEF(WorkspaceNodeQuatVec3Quat)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Length)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Mix)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec3Normalize)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Mix)
        SERIALIZE_NODE_DEF(WorkspaceNodeVec4Normalize)

        // Conversions
        SERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToMat4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToVec3)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToVec4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToFloat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToVec4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvAngleAxisToQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvEulerToQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToAngleAxis)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToEuler)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToFloat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToMat4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec3Vec3ToQuat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec3FloatToVec4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec3ToFloat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToFloat)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToMat4)
        SERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToVec3Float)

        // Projections
        SERIALIZE_NODE_DEF(WorkspaceNodeProjFrustum)
        SERIALIZE_NODE_DEF(WorkspaceNodeProjOrtho)
        SERIALIZE_NODE_DEF(WorkspaceNodeProjPerspective)

        // Logical
        SERIALIZE_NODE_DEF(WorkspaceNodeBoolAnd)
        SERIALIZE_NODE_DEF(WorkspaceNodeBoolNot)
        SERIALIZE_NODE_DEF(WorkspaceNodeBoolOr)
        SERIALIZE_NODE_VALUES_DEF(WorkspaceNodeBoolValue)
        SERIALIZE_NODE_DEF(WorkspaceNodeBoolXor)
        SERIALIZE_NODE_DEF(WorkspaceNodeCmpEqual)
        SERIALIZE_NODE_DEF(WorkspaceNodeCmpNotEqual)
        SERIALIZE_NODE_DEF(WorkspaceNodeCmpSmaller)
        SERIALIZE_NODE_DEF(WorkspaceNodeCmpSmallerEqual)
        SERIALIZE_NODE_DEF(WorkspaceNodePick)

        // Miscellaneous
        // Other are hard coded instead of generated by a macro
        SERIALIZE_NODE_DEF(WorkspaceNodeTime)

        std::shared_ptr<WorkspaceNode> SerializeNode_WorkspaceNodeEmbeddedObject(Scene& scene, std::istream& stream);

      private:
        SerDerTab    m_Tabs;
        StreamExpect m_StreamExpect;
    };
}
#pragma once

#include <ostream>

#include "SerDerTab.h"

#include "IDeserializer.h"

#define DESERIALIZE_NODE_DEF(type)                                                                                                                                                 \
    void DeserializeNode_##type(type& node, std::ostream& stream) {                                                                                                                \
        DeserializeNode(#type, node, false, stream);                                                                                                                               \
    }

#define DESERIALIZE_NODE_VALUES_DEF(type)                                                                                                                                          \
    void DeserializeNode_##type(WorkspaceNode& node, std::ostream& stream) {                                                                                                       \
        DeserializeNode(#type, node, true, stream);                                                                                                                                \
    }

namespace AVC3T {
    class TextDeserializer : public IDeserializer {
      public:
        virtual void Deserialize(const Workspace& workspace, std::ostream& stream) override;

      private:
        void DeserializeElement(const std::shared_ptr<WorkspaceElement>& node, std::ostream& stream);
        void DeserializeNode(const char* name, WorkspaceNode& node, bool deserializeValues, std::ostream& stream);
        void DeserializeNodeName(const char* name, std::ostream& stream);
        void DeserializeNodeProperties(WorkspaceNode& node, bool deserializeValues, std::ostream& stream);

        void DeserializeIOValue(const WorkspaceIOType& type, const WorkspaceIOValue& value, std::ostream& stream);
        void DeserializeOutputs(std::vector<std::shared_ptr<WorkspaceOutputPin>>& outputs, bool deserializeValues, std::ostream& stream);

        // Values
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeFloatValue)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeMat4Value)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeQuatValue)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfRotationValue)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfScaleValue)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeTransfTranslValue)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeVec3Value)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeVec4Value)

        // Operator
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatAdd)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatDivide)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMultiply)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMultMat4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMultQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMultVec3)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMultVec4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatPower)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatSubstract)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Add)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Mult)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4MultVec4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Substract)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatMult)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Add)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Dot)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Multiply)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Substract)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Add)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Dot)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Multiply)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Substract)

        // Transformations
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfLookAt)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationVector)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationX)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationY)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfRotationZ)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfScale)
        DESERIALIZE_NODE_DEF(WorkspaceNodeTransfTransl)

        // Functions
        DESERIALIZE_NODE_DEF(WorkspaceNodeAbs)
        DESERIALIZE_NODE_DEF(WorkspaceNodeAcos)
        DESERIALIZE_NODE_DEF(WorkspaceNodeAsin)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCeil)
        DESERIALIZE_NODE_DEF(WorkspaceNodeClamp)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCos)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloatMix)
        DESERIALIZE_NODE_DEF(WorkspaceNodeFloor)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMod)
        DESERIALIZE_NODE_DEF(WorkspaceNodeSign)
        DESERIALIZE_NODE_DEF(WorkspaceNodeSin)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Decompose)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Determinant)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Inverse)
        DESERIALIZE_NODE_DEF(WorkspaceNodeMat4Transpose)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatConjugate)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatInverse)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatLength)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatLerp)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatNormalize)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatSlerp)
        DESERIALIZE_NODE_DEF(WorkspaceNodeQuatVec3Quat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Length)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Mix)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec3Normalize)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Mix)
        DESERIALIZE_NODE_DEF(WorkspaceNodeVec4Normalize)

        // Conversions
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToMat4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToVec3)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvFloatToVec4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToFloat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvMat4ToVec4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvAngleAxisToQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvEulerToQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToAngleAxis)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToEuler)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToFloat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvQuatToMat4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec3Vec3ToQuat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec3FloatToVec4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec3ToFloat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToFloat)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToMat4)
        DESERIALIZE_NODE_DEF(WorkspaceNodeConvVec4ToVec3Float)

        // Projections
        DESERIALIZE_NODE_DEF(WorkspaceNodeProjFrustum)
        DESERIALIZE_NODE_DEF(WorkspaceNodeProjOrtho)
        DESERIALIZE_NODE_DEF(WorkspaceNodeProjPerspective)

        // Logical
        DESERIALIZE_NODE_DEF(WorkspaceNodeBoolAnd)
        DESERIALIZE_NODE_DEF(WorkspaceNodeBoolNot)
        DESERIALIZE_NODE_DEF(WorkspaceNodeBoolOr)
        DESERIALIZE_NODE_VALUES_DEF(WorkspaceNodeBoolValue)
        DESERIALIZE_NODE_DEF(WorkspaceNodeBoolXor)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCmpEqual)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCmpNotEqual)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCmpSmaller)
        DESERIALIZE_NODE_DEF(WorkspaceNodeCmpSmallerEqual)
        DESERIALIZE_NODE_DEF(WorkspaceNodePick)

        // Object
        void DeserializeNode_WorkspaceNodeEmbeddedObject(WorkspaceNodeEmbeddedObject& node, std::ostream& stream);
        void DeserializeNode_WorkspaceNodeExternalObject(WorkspaceNodeExternalObject& node, std::ostream& stream);
        void DeserializeNode_WorkspaceNodeSceneObject(WorkspaceNodeSceneObject& node, std::ostream& stream);

        // Miscellaneous
        void DeserializeNode_WorkspaceNodeCamera(WorkspaceNodeCamera& node, std::ostream& stream);
        void DeserializeNode_WorkspaceNodeText(WorkspaceNodeText& node, std::ostream& stream);
        DESERIALIZE_NODE_DEF(WorkspaceNodeTime)

      private:
        SerDerTab m_Tabs;
    };
}

#undef DESERIALIZE_NODE_DEF
#undef DESERIALIZE_NODE_VALUES_DEF

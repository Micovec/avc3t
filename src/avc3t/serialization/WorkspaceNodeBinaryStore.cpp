#include "WorkspaceNodeBinaryStore.h"

#define ADD_NODE_TO_STORE(type) #type

namespace AVC3T {
    size_t WorkspaceNodeBinaryStore::GetNodeType(const std::string& nodeName) {
        return GetInstance().m_NodeNameToType.at(nodeName);
    }

    const std::string& WorkspaceNodeBinaryStore::GetNodeName(size_t nodeType) {
        return GetInstance().m_NodeTypeToName.at(nodeType);
    }

    WorkspaceNodeBinaryStore::WorkspaceNodeBinaryStore(std::initializer_list<std::string> initList) {
        size_t nodeType = 0;
        for (auto it = initList.begin(); it != initList.end(); ++it, ++nodeType) {
            m_NodeTypeToName.insert({nodeType, *it});
            m_NodeNameToType.insert({*it, nodeType});
        }
    }

    const WorkspaceNodeBinaryStore& WorkspaceNodeBinaryStore::GetInstance() {
        static WorkspaceNodeBinaryStore store = {
            // Value
            ADD_NODE_TO_STORE(WorkspaceNodeFloatValue), ADD_NODE_TO_STORE(WorkspaceNodeMat4Value), ADD_NODE_TO_STORE(WorkspaceNodeQuatValue),
            ADD_NODE_TO_STORE(WorkspaceNodeVec3Value), ADD_NODE_TO_STORE(WorkspaceNodeVec4Value), ADD_NODE_TO_STORE(WorkspaceNodeTransfRotationValue),
            ADD_NODE_TO_STORE(WorkspaceNodeTransfScaleValue), ADD_NODE_TO_STORE(WorkspaceNodeTransfTranslValue),

            // Operator
            ADD_NODE_TO_STORE(WorkspaceNodeFloatAdd), ADD_NODE_TO_STORE(WorkspaceNodeFloatDivide), ADD_NODE_TO_STORE(WorkspaceNodeFloatMultiply),
            ADD_NODE_TO_STORE(WorkspaceNodeFloatMultMat4), ADD_NODE_TO_STORE(WorkspaceNodeFloatMultQuat), ADD_NODE_TO_STORE(WorkspaceNodeFloatMultVec3),
            ADD_NODE_TO_STORE(WorkspaceNodeFloatMultVec4), ADD_NODE_TO_STORE(WorkspaceNodeFloatPower), ADD_NODE_TO_STORE(WorkspaceNodeFloatSubstract),
            ADD_NODE_TO_STORE(WorkspaceNodeMat4Add), ADD_NODE_TO_STORE(WorkspaceNodeMat4Mult), ADD_NODE_TO_STORE(WorkspaceNodeMat4MultVec4),
            ADD_NODE_TO_STORE(WorkspaceNodeMat4Substract), ADD_NODE_TO_STORE(WorkspaceNodeVec3Add), ADD_NODE_TO_STORE(WorkspaceNodeVec3Dot),
            ADD_NODE_TO_STORE(WorkspaceNodeVec3Multiply), ADD_NODE_TO_STORE(WorkspaceNodeVec3Substract), ADD_NODE_TO_STORE(WorkspaceNodeVec4Add),
            ADD_NODE_TO_STORE(WorkspaceNodeVec4Dot), ADD_NODE_TO_STORE(WorkspaceNodeVec4Multiply), ADD_NODE_TO_STORE(WorkspaceNodeVec4Substract)};

        return store;
    }
}

#undef ADD_NODE_TO_STORE

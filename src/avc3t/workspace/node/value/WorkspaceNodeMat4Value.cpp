#include "WorkspaceNodeMat4Value.h"

namespace AVC3T {
    WorkspaceNodeMat4Value::WorkspaceNodeMat4Value() :
        WorkspaceNode("Mat4", {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_Matrix})}, {IM_COL32(190, 35, 52, 255)}), m_Matrix(1.0f) {}

    WorkspaceNodeMat4Value::WorkspaceNodeMat4Value(const WorkspaceNodeMat4Value& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_Matrix})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(other.m_Matrix) {}

    void WorkspaceNodeMat4Value::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
#include "WorkspaceNodeTransfScaleValue.h"

namespace AVC3T {
    WorkspaceNodeTransfScaleValue::WorkspaceNodeTransfScaleValue() :
        WorkspaceNode("Scale", {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1111101111011110)}, {IM_COL32(190, 35, 52, 255)}), m_Matrix(1.0f) {}

    WorkspaceNodeTransfScaleValue::WorkspaceNodeTransfScaleValue(const WorkspaceNodeTransfScaleValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1111101111011110)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfScaleValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
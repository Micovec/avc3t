#include "WorkspaceNodeTransfRotationValue.h"

namespace AVC3T {
    WorkspaceNodeTransfRotationValue::WorkspaceNodeTransfRotationValue() :
        WorkspaceNode("Rotation", {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1111100010001000)}, {IM_COL32(190, 35, 52, 255)}), m_Matrix(1.0f) {}

    WorkspaceNodeTransfRotationValue::WorkspaceNodeTransfRotationValue(const WorkspaceNodeTransfRotationValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1111100010001000)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfRotationValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
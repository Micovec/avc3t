#include "WorkspaceNodeTransfTranslValue.h"

namespace AVC3T {
    WorkspaceNodeTransfTranslValue::WorkspaceNodeTransfTranslValue() :
        WorkspaceNode("Translation", {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1000111111111111)}, {IM_COL32(190, 35, 52, 255)}), m_Matrix(1.0f) {}

    WorkspaceNodeTransfTranslValue::WorkspaceNodeTransfTranslValue(const WorkspaceNodeTransfTranslValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, 0b1000111111111111)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfTranslValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
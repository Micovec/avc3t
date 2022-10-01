#include "WorkspaceNodeQuatValue.h"

namespace AVC3T {
    WorkspaceNodeQuatValue::WorkspaceNodeQuatValue() :
        WorkspaceNode("Quat", {}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_Value})}, {IM_COL32(190, 35, 52, 255)}), m_Value(0, 0, 0, 0) {}

    WorkspaceNodeQuatValue::WorkspaceNodeQuatValue(const WorkspaceNodeQuatValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_Value})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Value(other.m_Value) {}

    void WorkspaceNodeQuatValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
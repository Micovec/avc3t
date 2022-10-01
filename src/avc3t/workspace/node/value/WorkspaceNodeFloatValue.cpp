#include "WorkspaceNodeFloatValue.h"

namespace AVC3T {
    WorkspaceNodeFloatValue::WorkspaceNodeFloatValue() :
        WorkspaceNode("Float", {}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_Value})}, {IM_COL32(190, 35, 52, 255)}), m_Value(0) {}

    WorkspaceNodeFloatValue::WorkspaceNodeFloatValue(const WorkspaceNodeFloatValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_Value})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Value(other.m_Value) {}

    void WorkspaceNodeFloatValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
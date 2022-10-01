#include "WorkspaceNodeBoolValue.h"

namespace AVC3T {
    WorkspaceNodeBoolValue::WorkspaceNodeBoolValue() :
        WorkspaceNode("Bool", {}, {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue})}, {IM_COL32(190, 35, 52, 255)}), m_OutputValue(true) {}

    WorkspaceNodeBoolValue::WorkspaceNodeBoolValue(const WorkspaceNodeBoolValue& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(true) {}

    void WorkspaceNodeBoolValue::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
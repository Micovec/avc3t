#include "WorkspaceNodeVec4Value.h"

#include <iostream>
namespace AVC3T {
    WorkspaceNodeVec4Value::WorkspaceNodeVec4Value() : WorkspaceNode("Vec4", {}, {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_Vec4})}, {IM_COL32(190, 35, 52, 255)}), m_Vec4() {}

    WorkspaceNodeVec4Value::WorkspaceNodeVec4Value(const WorkspaceNodeVec4Value& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_Vec4})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Vec4(other.m_Vec4) {}

    void WorkspaceNodeVec4Value::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
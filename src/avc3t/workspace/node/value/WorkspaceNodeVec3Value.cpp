#include "WorkspaceNodeVec3Value.h"

#include <iostream>
namespace AVC3T {
    WorkspaceNodeVec3Value::WorkspaceNodeVec3Value() : WorkspaceNode("Vec3", {}, {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Vec3})}, {IM_COL32(190, 35, 52, 255)}), m_Vec3() {}

    WorkspaceNodeVec3Value::WorkspaceNodeVec3Value(const WorkspaceNodeVec3Value& other) :
        WorkspaceNode(other.m_Title, {}, {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_Vec3})}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Vec3(other.m_Vec3) {}

    void WorkspaceNodeVec3Value::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
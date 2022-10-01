#include "WorkspaceNodeVec3Length.h"

namespace AVC3T {
    WorkspaceNodeVec3Length::WorkspaceNodeVec3Length() :
        WorkspaceNode("Length Vec3", {WorkspaceNodeInput(WorkspaceIOType_Vec3)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeVec3Length::WorkspaceNodeVec3Length(const WorkspaceNodeVec3Length& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeVec3Length::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::length(*input0->Link->OutputPin.Output.Value.vec3);
    }
}
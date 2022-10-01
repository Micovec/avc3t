#include "WorkspaceNodeFloatMultVec3.h"

namespace AVC3T {
    WorkspaceNodeFloatMultVec3::WorkspaceNodeFloatMultVec3() :
        WorkspaceNode("Float * Vec3", {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeFloatMultVec3::WorkspaceNodeFloatMultVec3(const WorkspaceNodeFloatMultVec3& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeFloatMultVec3::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = (*input0->Link->OutputPin.Output.Value.f) * (*input1->Link->OutputPin.Output.Value.vec3);
    }
}
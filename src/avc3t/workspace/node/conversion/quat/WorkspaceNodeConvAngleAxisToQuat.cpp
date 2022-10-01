#include "WorkspaceNodeConvAngleAxisToQuat.h"

namespace AVC3T {
    WorkspaceNodeConvAngleAxisToQuat::WorkspaceNodeConvAngleAxisToQuat() :
        WorkspaceNode("Angle + Axis -> Quat", {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeConvAngleAxisToQuat::WorkspaceNodeConvAngleAxisToQuat(const WorkspaceNodeConvAngleAxisToQuat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeConvAngleAxisToQuat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = glm::angleAxis(*input0->Link->OutputPin.Output.Value.f, *input1->Link->OutputPin.Output.Value.vec3);
    }
}
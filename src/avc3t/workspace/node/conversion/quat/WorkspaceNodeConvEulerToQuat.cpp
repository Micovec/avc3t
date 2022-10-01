#include "WorkspaceNodeConvEulerToQuat.h"

namespace AVC3T {
    WorkspaceNodeConvEulerToQuat::WorkspaceNodeConvEulerToQuat() :
        WorkspaceNode("Euler -> Quat",
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "x"), WorkspaceNodeInput(WorkspaceIOType_Float, "y"), WorkspaceNodeInput(WorkspaceIOType_Float, "z")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeConvEulerToQuat::WorkspaceNodeConvEulerToQuat(const WorkspaceNodeConvEulerToQuat& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "x"), WorkspaceNodeInput(WorkspaceIOType_Float, "y"), WorkspaceNodeInput(WorkspaceIOType_Float, "z")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeConvEulerToQuat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        m_OutputValue = glm::quat(glm::vec3(*input0->Link->OutputPin.Output.Value.f, *input1->Link->OutputPin.Output.Value.f, *input2->Link->OutputPin.Output.Value.f));
    }
}
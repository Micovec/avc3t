#include "WorkspaceNodeFloatMultMat4.h"

namespace AVC3T {
    WorkspaceNodeFloatMultMat4::WorkspaceNodeFloatMultMat4() :
        WorkspaceNode("Float * Mat4", {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(1.0f) {}

    WorkspaceNodeFloatMultMat4::WorkspaceNodeFloatMultMat4(const WorkspaceNodeFloatMultMat4& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float), WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(1.0f) {}

    void WorkspaceNodeFloatMultMat4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = (*input0->Link->OutputPin.Output.Value.f) * (*input1->Link->OutputPin.Output.Value.mat4);
    }
}
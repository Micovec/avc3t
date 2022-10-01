#include "WorkspaceNodeClamp.h"

namespace AVC3T {
    WorkspaceNodeClamp::WorkspaceNodeClamp() :
        WorkspaceNode("Clamp",
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "value"), WorkspaceNodeInput(WorkspaceIOType_Float, "min"), WorkspaceNodeInput(WorkspaceIOType_Float, "max")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeClamp::WorkspaceNodeClamp(const WorkspaceNodeClamp& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "value"), WorkspaceNodeInput(WorkspaceIOType_Float, "min"), WorkspaceNodeInput(WorkspaceIOType_Float, "max")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeClamp::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        m_OutputValue = std::clamp(*input0->Link->OutputPin.Output.Value.f, *input1->Link->OutputPin.Output.Value.f, *input2->Link->OutputPin.Output.Value.f);
    }
}
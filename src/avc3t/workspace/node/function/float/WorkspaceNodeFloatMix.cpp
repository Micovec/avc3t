#include "WorkspaceNodeFloatMix.h"

namespace AVC3T {
    WorkspaceNodeFloatMix::WorkspaceNodeFloatMix() :
        WorkspaceNode("Mix float",
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "from"), WorkspaceNodeInput(WorkspaceIOType_Float, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeFloatMix::WorkspaceNodeFloatMix(const WorkspaceNodeFloatMix& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "from"), WorkspaceNodeInput(WorkspaceIOType_Float, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeFloatMix::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        float from = *input0->Link->OutputPin.Output.Value.f;
        float to   = *input1->Link->OutputPin.Output.Value.f;

        m_OutputValue = from + (to - from) * (*input2->Link->OutputPin.Output.Value.f);
    }
}
#include "WorkspaceNodeQuatSlerp.h"

namespace AVC3T {
    WorkspaceNodeQuatSlerp::WorkspaceNodeQuatSlerp() :
        WorkspaceNode("Slerp Quat",
                      {WorkspaceNodeInput(WorkspaceIOType_Quat, "from"), WorkspaceNodeInput(WorkspaceIOType_Quat, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeQuatSlerp::WorkspaceNodeQuatSlerp(const WorkspaceNodeQuatSlerp& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Quat, "from"), WorkspaceNodeInput(WorkspaceIOType_Quat, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeQuatSlerp::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin> input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        m_OutputValue = glm::slerp(*input0->Link->OutputPin.Output.Value.quat, *input1->Link->OutputPin.Output.Value.quat, *input2->Link->OutputPin.Output.Value.f);
    }
}
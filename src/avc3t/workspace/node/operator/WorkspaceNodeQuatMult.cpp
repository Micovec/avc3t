#include "WorkspaceNodeQuatMult.h"

namespace AVC3T {
    WorkspaceNodeQuatMult::WorkspaceNodeQuatMult() :
        WorkspaceNode("Quat * Quat", {WorkspaceNodeInput(WorkspaceIOType_Quat), WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeQuatMult::WorkspaceNodeQuatMult(const WorkspaceNodeQuatMult& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat), WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeQuatMult::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = (*input0->Link->OutputPin.Output.Value.quat) * (*input1->Link->OutputPin.Output.Value.quat);
    }
}
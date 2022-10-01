#include "WorkspaceNodeQuatNormalize.h"

namespace AVC3T {
    WorkspaceNodeQuatNormalize::WorkspaceNodeQuatNormalize() :
        WorkspaceNode("Normalize Quat", {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeQuatNormalize::WorkspaceNodeQuatNormalize(const WorkspaceNodeQuatNormalize& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeQuatNormalize::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::normalize(*input0->Link->OutputPin.Output.Value.quat);
    }
}
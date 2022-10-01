#include "WorkspaceNodeQuatLength.h"

namespace AVC3T {
    WorkspaceNodeQuatLength::WorkspaceNodeQuatLength() :
        WorkspaceNode("Length Quat", {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeQuatLength::WorkspaceNodeQuatLength(const WorkspaceNodeQuatLength& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeQuatLength::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::length(*input0->Link->OutputPin.Output.Value.quat);
    }
}
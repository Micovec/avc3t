#include "WorkspaceNodeConvQuatToMat4.h"

namespace AVC3T {
    WorkspaceNodeConvQuatToMat4::WorkspaceNodeConvQuatToMat4() :
        WorkspaceNode("Quat -> Mat4", {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeConvQuatToMat4::WorkspaceNodeConvQuatToMat4(const WorkspaceNodeConvQuatToMat4& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeConvQuatToMat4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::mat4(*input0->Link->OutputPin.Output.Value.quat);
    }
}
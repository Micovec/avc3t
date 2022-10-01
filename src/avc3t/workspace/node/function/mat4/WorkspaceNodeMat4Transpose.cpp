#include "WorkspaceNodeMat4Transpose.h"

namespace AVC3T {
    WorkspaceNodeMat4Transpose::WorkspaceNodeMat4Transpose() :
        WorkspaceNode("Transpose Mat4", {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(1.0f) {}

    WorkspaceNodeMat4Transpose::WorkspaceNodeMat4Transpose(const WorkspaceNodeMat4Transpose& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(1.0f) {}

    void WorkspaceNodeMat4Transpose::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::transpose(*input0->Link->OutputPin.Output.Value.mat4);
    }
}
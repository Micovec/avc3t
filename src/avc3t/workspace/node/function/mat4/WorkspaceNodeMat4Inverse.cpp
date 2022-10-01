#include "WorkspaceNodeMat4Inverse.h"

namespace AVC3T {
    WorkspaceNodeMat4Inverse::WorkspaceNodeMat4Inverse() :
        WorkspaceNode("Inverse Mat4", {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(1.0f) {}

    WorkspaceNodeMat4Inverse::WorkspaceNodeMat4Inverse(const WorkspaceNodeMat4Inverse& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(1.0f) {}

    void WorkspaceNodeMat4Inverse::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::inverse(*input0->Link->OutputPin.Output.Value.mat4);
    }
}
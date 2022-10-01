#include "WorkspaceNodeMat4Determinant.h"

namespace AVC3T {
    WorkspaceNodeMat4Determinant::WorkspaceNodeMat4Determinant() :
        WorkspaceNode("Determinant Mat4", {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeMat4Determinant::WorkspaceNodeMat4Determinant(const WorkspaceNodeMat4Determinant& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeMat4Determinant::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::determinant(*input0->Link->OutputPin.Output.Value.mat4);
    }
}
#include "WorkspaceNodeMat4Mult.h"

namespace AVC3T {
    WorkspaceNodeMat4Mult::WorkspaceNodeMat4Mult() :
        WorkspaceNode("Mat4 * Mat4", {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_Matrix}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeMat4Mult::WorkspaceNodeMat4Mult(const WorkspaceNodeMat4Mult& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_Matrix}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeMat4Mult::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_Matrix = (*input0->Link->OutputPin.Output.Value.mat4) * (*input1->Link->OutputPin.Output.Value.mat4);
    }
}
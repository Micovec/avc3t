#include "WorkspaceNodeTransfRotationY.h"

namespace AVC3T {
    WorkspaceNodeTransfRotationY::WorkspaceNodeTransfRotationY() :
        WorkspaceNode("Rotation euler angle Y", {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeTransfRotationY::WorkspaceNodeTransfRotationY(const WorkspaceNodeTransfRotationY& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfRotationY::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input = m_InputPins[0];

        if (input->Link == nullptr)
            return;

        m_Matrix = glm::rotate(glm::mat4(1.0f), *input->Link->OutputPin.Output.Value.f, glm::vec3(0, 1, 0));
    }
}
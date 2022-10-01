#include "WorkspaceNodeTransfScale.h"

namespace AVC3T {
    WorkspaceNodeTransfScale::WorkspaceNodeTransfScale() :
        WorkspaceNode("Scale", {WorkspaceNodeInput(WorkspaceIOType_Vec3)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeTransfScale::WorkspaceNodeTransfScale(const WorkspaceNodeTransfScale& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3)}, {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfScale::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input = m_InputPins[0];

        if (input->Link == nullptr)
            return;

        m_Matrix = glm::scale(glm::mat4(1.0f), *input->Link->OutputPin.Output.Value.vec3);
    }
}
#include "WorkspaceNodeTransfLookAt.h"

namespace AVC3T {
    WorkspaceNodeTransfLookAt::WorkspaceNodeTransfLookAt() :
        WorkspaceNode("Look at",
                      {WorkspaceNodeInput(WorkspaceIOType_Vec3, "eye"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "center"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "up")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeTransfLookAt::WorkspaceNodeTransfLookAt(const WorkspaceNodeTransfLookAt& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Vec3, "eye"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "center"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "up")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfLookAt::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& inputEye    = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& inputCenter = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& inputUp     = m_InputPins[2];

        if (inputEye->Link == nullptr || inputCenter->Link == nullptr || inputUp->Link == nullptr)
            return;

        m_Matrix = glm::lookAt(*inputEye->Link->OutputPin.Output.Value.vec3, *inputCenter->Link->OutputPin.Output.Value.vec3, *inputUp->Link->OutputPin.Output.Value.vec3);
    }
}
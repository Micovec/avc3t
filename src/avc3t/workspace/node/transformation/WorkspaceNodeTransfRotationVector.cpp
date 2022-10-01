#include "WorkspaceNodeTransfRotationVector.h"

namespace AVC3T {
    WorkspaceNodeTransfRotationVector::WorkspaceNodeTransfRotationVector() :
        WorkspaceNode("Rotation - vector + angle", {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Float)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeTransfRotationVector::WorkspaceNodeTransfRotationVector(const WorkspaceNodeTransfRotationVector& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Float)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeTransfRotationVector::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& inputVector = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& inputAngle  = m_InputPins[1];

        if (inputVector->Link == nullptr || inputAngle->Link == nullptr)
            return;

        m_Matrix = glm::rotate(glm::mat4(1.0f), *inputAngle->Link->OutputPin.Output.Value.f, *inputVector->Link->OutputPin.Output.Value.vec3);
    }
}
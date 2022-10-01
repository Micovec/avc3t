#include "WorkspaceNodeQuatVec3Quat.h"

namespace AVC3T {
    WorkspaceNodeQuatVec3Quat::WorkspaceNodeQuatVec3Quat() :
        WorkspaceNode("Quat * Vec3 * Quat*", {WorkspaceNodeInput(WorkspaceIOType_Quat), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeQuatVec3Quat::WorkspaceNodeQuatVec3Quat(const WorkspaceNodeQuatVec3Quat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeQuatVec3Quat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        glm::quat q    = *input0->Link->OutputPin.Output.Value.quat;
        glm::vec3 vec  = *input1->Link->OutputPin.Output.Value.vec3;
        glm::quat conj = glm::conjugate(q);

        m_OutputValue = q * vec * conj;
    }
}
#include "WorkspaceNodeConvVec3Vec3ToQuat.h"

namespace AVC3T {
    WorkspaceNodeConvVec3Vec3ToQuat::WorkspaceNodeConvVec3Vec3ToQuat() :
        WorkspaceNode("Vec3 + Vec3 -> Quat", {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeConvVec3Vec3ToQuat::WorkspaceNodeConvVec3Vec3ToQuat(const WorkspaceNodeConvVec3Vec3ToQuat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeConvVec3Vec3ToQuat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = glm::quat(*input0->Link->OutputPin.Output.Value.vec3, *input1->Link->OutputPin.Output.Value.vec3);
    }
}
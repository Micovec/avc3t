#include "WorkspaceNodeConvMat4ToQuat.h"

namespace AVC3T {
    WorkspaceNodeConvMat4ToQuat::WorkspaceNodeConvMat4ToQuat() :
        WorkspaceNode("Mat4 -> Quat", {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0, 0, 0, 0) {}

    WorkspaceNodeConvMat4ToQuat::WorkspaceNodeConvMat4ToQuat(const WorkspaceNodeConvMat4ToQuat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {WorkspaceNodeOutput(WorkspaceIOType_Quat, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(0, 0, 0, 0) {}

    void WorkspaceNodeConvMat4ToQuat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = *input0->Link->OutputPin.Output.Value.mat4;
    }
}
#include "WorkspaceNodeMat4MultVec4.h"

namespace AVC3T {
    WorkspaceNodeMat4MultVec4::WorkspaceNodeMat4MultVec4() :
        WorkspaceNode("Mat4 * Vec4", {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(1.0f) {}

    WorkspaceNodeMat4MultVec4::WorkspaceNodeMat4MultVec4(const WorkspaceNodeMat4MultVec4& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(1.0f) {}

    void WorkspaceNodeMat4MultVec4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin> input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin> input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = (*input0->Link->OutputPin.Output.Value.mat4) * (*input1->Link->OutputPin.Output.Value.vec4);
    }
}
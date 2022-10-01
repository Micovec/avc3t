#include "WorkspaceNodeConvVec4ToMat4.h"

namespace AVC3T {
    WorkspaceNodeConvVec4ToMat4::WorkspaceNodeConvVec4ToMat4() :
        WorkspaceNode("4x Vec4 -> Mat4",
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 1"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 2"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 3"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 4"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(1.0f) {}

    WorkspaceNodeConvVec4ToMat4::WorkspaceNodeConvVec4ToMat4(const WorkspaceNodeConvVec4ToMat4& other) :
        WorkspaceNode(other.m_Title,
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 1"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 2"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 3"),
                          WorkspaceNodeInput(WorkspaceIOType_Vec4, "col 4"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(1.0f) {}

    void WorkspaceNodeConvVec4ToMat4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];
        std::shared_ptr<WorkspaceInputPin>& input3 = m_InputPins[3];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr || input3->Link == nullptr)
            return;

        m_OutputValue = glm::mat4(*input0->Link->OutputPin.Output.Value.vec4, *input1->Link->OutputPin.Output.Value.vec4, *input2->Link->OutputPin.Output.Value.vec4,
                                  *input3->Link->OutputPin.Output.Value.vec4);
    }
}
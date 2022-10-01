#include "WorkspaceNodeConvMat4ToVec4.h"

namespace AVC3T {
    WorkspaceNodeConvMat4ToVec4::WorkspaceNodeConvMat4ToVec4() :
        WorkspaceNode("Mat4 -> 4x Vec4", {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue0}, -1, "col 1"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue1}, -1, "col 2"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue2}, -1, "col 3"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue3}, -1, "col 4"),
                      },
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0) {}

    WorkspaceNodeConvMat4ToVec4::WorkspaceNodeConvMat4ToVec4(const WorkspaceNodeConvMat4ToVec4& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue0}, -1, "col 1"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue1}, -1, "col 2"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue2}, -1, "col 3"),
                          WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue3}, -1, "col 4"),
                      },
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0) {}

    void WorkspaceNodeConvMat4ToVec4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue0 = input0->Link->OutputPin.Output.Value.mat4->operator[](0);
        m_OutputValue1 = input0->Link->OutputPin.Output.Value.mat4->operator[](1);
        m_OutputValue2 = input0->Link->OutputPin.Output.Value.mat4->operator[](2);
        m_OutputValue3 = input0->Link->OutputPin.Output.Value.mat4->operator[](3);
    }
}
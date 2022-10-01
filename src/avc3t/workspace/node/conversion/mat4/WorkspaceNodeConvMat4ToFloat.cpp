#include "WorkspaceNodeConvMat4ToFloat.h"

namespace AVC3T {
    WorkspaceNodeConvMat4ToFloat::WorkspaceNodeConvMat4ToFloat() :
        WorkspaceNode("Mat4 -> 16x Float", {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "a11"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "a12"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "a13"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue3}, -1, "a14"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue4}, -1, "a21"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue5}, -1, "a22"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue6}, -1, "a23"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue7}, -1, "a24"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue8}, -1, "a31"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue9}, -1, "a32"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue10}, -1, "a33"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue11}, -1, "a34"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue12}, -1, "a41"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue13}, -1, "a42"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue14}, -1, "a43"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue15}, -1, "a44"),
                      },
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0), m_OutputValue4(0), m_OutputValue5(0), m_OutputValue6(0), m_OutputValue7(0), m_OutputValue8(0),
        m_OutputValue9(0), m_OutputValue10(0), m_OutputValue11(0), m_OutputValue12(0), m_OutputValue13(0), m_OutputValue14(0), m_OutputValue15(0) {}

    WorkspaceNodeConvMat4ToFloat::WorkspaceNodeConvMat4ToFloat(const WorkspaceNodeConvMat4ToFloat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)},
                      {
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "a11"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "a12"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "a13"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue3}, -1, "a14"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue4}, -1, "a21"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue5}, -1, "a22"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue6}, -1, "a23"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue7}, -1, "a24"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue8}, -1, "a31"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue9}, -1, "a32"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue10}, -1, "a33"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue11}, -1, "a34"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue12}, -1, "a41"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue13}, -1, "a42"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue14}, -1, "a43"),
                          WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue15}, -1, "a44"),
                      },
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0), m_OutputValue4(0), m_OutputValue5(0), m_OutputValue6(0), m_OutputValue7(0), m_OutputValue8(0),
        m_OutputValue9(0), m_OutputValue10(0), m_OutputValue11(0), m_OutputValue12(0), m_OutputValue13(0), m_OutputValue14(0), m_OutputValue15(0) {}

    void WorkspaceNodeConvMat4ToFloat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue0  = input0->Link->OutputPin.Output.Value.mat4->operator[](0)[0];
        m_OutputValue1  = input0->Link->OutputPin.Output.Value.mat4->operator[](1)[0];
        m_OutputValue2  = input0->Link->OutputPin.Output.Value.mat4->operator[](2)[0];
        m_OutputValue3  = input0->Link->OutputPin.Output.Value.mat4->operator[](3)[0];
        m_OutputValue4  = input0->Link->OutputPin.Output.Value.mat4->operator[](0)[1];
        m_OutputValue5  = input0->Link->OutputPin.Output.Value.mat4->operator[](1)[1];
        m_OutputValue6  = input0->Link->OutputPin.Output.Value.mat4->operator[](2)[1];
        m_OutputValue7  = input0->Link->OutputPin.Output.Value.mat4->operator[](3)[1];
        m_OutputValue8  = input0->Link->OutputPin.Output.Value.mat4->operator[](0)[2];
        m_OutputValue9  = input0->Link->OutputPin.Output.Value.mat4->operator[](1)[2];
        m_OutputValue10 = input0->Link->OutputPin.Output.Value.mat4->operator[](2)[2];
        m_OutputValue11 = input0->Link->OutputPin.Output.Value.mat4->operator[](3)[2];
        m_OutputValue12 = input0->Link->OutputPin.Output.Value.mat4->operator[](0)[3];
        m_OutputValue13 = input0->Link->OutputPin.Output.Value.mat4->operator[](1)[3];
        m_OutputValue14 = input0->Link->OutputPin.Output.Value.mat4->operator[](2)[3];
        m_OutputValue15 = input0->Link->OutputPin.Output.Value.mat4->operator[](3)[3];
    }
}
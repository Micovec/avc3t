#include "WorkspaceNodeConvFloatToMat4.h"

namespace AVC3T {
    WorkspaceNodeConvFloatToMat4::WorkspaceNodeConvFloatToMat4() :
        WorkspaceNode("16x Float -> Mat4",
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "a11"), WorkspaceNodeInput(WorkspaceIOType_Float, "a12"), WorkspaceNodeInput(WorkspaceIOType_Float, "a13"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a14"), WorkspaceNodeInput(WorkspaceIOType_Float, "a21"), WorkspaceNodeInput(WorkspaceIOType_Float, "a22"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a23"), WorkspaceNodeInput(WorkspaceIOType_Float, "a24"), WorkspaceNodeInput(WorkspaceIOType_Float, "a31"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a32"), WorkspaceNodeInput(WorkspaceIOType_Float, "a33"), WorkspaceNodeInput(WorkspaceIOType_Float, "a34"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a41"), WorkspaceNodeInput(WorkspaceIOType_Float, "a42"), WorkspaceNodeInput(WorkspaceIOType_Float, "a43"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a44")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeConvFloatToMat4::WorkspaceNodeConvFloatToMat4(const WorkspaceNodeConvFloatToMat4& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "a11"), WorkspaceNodeInput(WorkspaceIOType_Float, "a12"), WorkspaceNodeInput(WorkspaceIOType_Float, "a13"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a14"), WorkspaceNodeInput(WorkspaceIOType_Float, "a21"), WorkspaceNodeInput(WorkspaceIOType_Float, "a22"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a23"), WorkspaceNodeInput(WorkspaceIOType_Float, "a24"), WorkspaceNodeInput(WorkspaceIOType_Float, "a31"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a32"), WorkspaceNodeInput(WorkspaceIOType_Float, "a33"), WorkspaceNodeInput(WorkspaceIOType_Float, "a34"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a41"), WorkspaceNodeInput(WorkspaceIOType_Float, "a42"), WorkspaceNodeInput(WorkspaceIOType_Float, "a43"),
                       WorkspaceNodeInput(WorkspaceIOType_Float, "a44")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeConvFloatToMat4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0  = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1  = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2  = m_InputPins[2];
        std::shared_ptr<WorkspaceInputPin>& input3  = m_InputPins[3];
        std::shared_ptr<WorkspaceInputPin>& input4  = m_InputPins[4];
        std::shared_ptr<WorkspaceInputPin>& input5  = m_InputPins[5];
        std::shared_ptr<WorkspaceInputPin>& input6  = m_InputPins[6];
        std::shared_ptr<WorkspaceInputPin>& input7  = m_InputPins[7];
        std::shared_ptr<WorkspaceInputPin>& input8  = m_InputPins[8];
        std::shared_ptr<WorkspaceInputPin>& input9  = m_InputPins[9];
        std::shared_ptr<WorkspaceInputPin>& input10 = m_InputPins[10];
        std::shared_ptr<WorkspaceInputPin>& input11 = m_InputPins[11];
        std::shared_ptr<WorkspaceInputPin>& input12 = m_InputPins[12];
        std::shared_ptr<WorkspaceInputPin>& input13 = m_InputPins[13];
        std::shared_ptr<WorkspaceInputPin>& input14 = m_InputPins[14];
        std::shared_ptr<WorkspaceInputPin>& input15 = m_InputPins[15];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr || input3->Link == nullptr || input4->Link == nullptr || input5->Link == nullptr ||
            input6->Link == nullptr || input7->Link == nullptr || input8->Link == nullptr || input9->Link == nullptr || input10->Link == nullptr || input11->Link == nullptr ||
            input12->Link == nullptr || input13->Link == nullptr || input14->Link == nullptr || input15->Link == nullptr)
            return;

        m_OutputValue[0][0] = *input0->Link->OutputPin.Output.Value.f;
        m_OutputValue[1][0] = *input1->Link->OutputPin.Output.Value.f;
        m_OutputValue[2][0] = *input2->Link->OutputPin.Output.Value.f;
        m_OutputValue[3][0] = *input3->Link->OutputPin.Output.Value.f;

        m_OutputValue[0][1] = *input4->Link->OutputPin.Output.Value.f;
        m_OutputValue[1][1] = *input5->Link->OutputPin.Output.Value.f;
        m_OutputValue[2][1] = *input6->Link->OutputPin.Output.Value.f;
        m_OutputValue[3][1] = *input7->Link->OutputPin.Output.Value.f;

        m_OutputValue[0][2] = *input8->Link->OutputPin.Output.Value.f;
        m_OutputValue[1][2] = *input9->Link->OutputPin.Output.Value.f;
        m_OutputValue[2][2] = *input10->Link->OutputPin.Output.Value.f;
        m_OutputValue[3][2] = *input11->Link->OutputPin.Output.Value.f;

        m_OutputValue[0][3] = *input12->Link->OutputPin.Output.Value.f;
        m_OutputValue[1][3] = *input13->Link->OutputPin.Output.Value.f;
        m_OutputValue[2][3] = *input14->Link->OutputPin.Output.Value.f;
        m_OutputValue[3][3] = *input15->Link->OutputPin.Output.Value.f;
    }
}
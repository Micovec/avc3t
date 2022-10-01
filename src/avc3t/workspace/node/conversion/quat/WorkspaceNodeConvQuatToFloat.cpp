#include "WorkspaceNodeConvQuatToFloat.h"

namespace AVC3T {
    WorkspaceNodeConvQuatToFloat::WorkspaceNodeConvQuatToFloat() :
        WorkspaceNode("Quat -> 4x Float", {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue3}, -1, "w")},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0) {}

    WorkspaceNodeConvQuatToFloat::WorkspaceNodeConvQuatToFloat(const WorkspaceNodeConvQuatToFloat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue3}, -1, "w")},
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0), m_OutputValue3(0) {}

    void WorkspaceNodeConvQuatToFloat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue0 = input0->Link->OutputPin.Output.Value.quat->x;
        m_OutputValue1 = input0->Link->OutputPin.Output.Value.quat->y;
        m_OutputValue2 = input0->Link->OutputPin.Output.Value.quat->z;
        m_OutputValue3 = input0->Link->OutputPin.Output.Value.quat->w;
    }
}
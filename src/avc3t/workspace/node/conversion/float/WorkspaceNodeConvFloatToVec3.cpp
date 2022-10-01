#include "WorkspaceNodeConvFloatToVec3.h"

namespace AVC3T {
    WorkspaceNodeConvFloatToVec3::WorkspaceNodeConvFloatToVec3() :
        WorkspaceNode("3x Float -> Vec3",
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "x"), WorkspaceNodeInput(WorkspaceIOType_Float, "y"), WorkspaceNodeInput(WorkspaceIOType_Float, "z")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeConvFloatToVec3::WorkspaceNodeConvFloatToVec3(const WorkspaceNodeConvFloatToVec3& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Float, "x"), WorkspaceNodeInput(WorkspaceIOType_Float, "y"), WorkspaceNodeInput(WorkspaceIOType_Float, "z")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeConvFloatToVec3::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        m_OutputValue.x = *input0->Link->OutputPin.Output.Value.f;
        m_OutputValue.y = *input1->Link->OutputPin.Output.Value.f;
        m_OutputValue.z = *input2->Link->OutputPin.Output.Value.f;
    }
}
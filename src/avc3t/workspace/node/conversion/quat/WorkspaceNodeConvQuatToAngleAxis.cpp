#include "WorkspaceNodeConvQuatToAngleAxis.h"

namespace AVC3T {
    WorkspaceNodeConvQuatToAngleAxis::WorkspaceNodeConvQuatToAngleAxis() :
        WorkspaceNode("Quat -> Angle + Axis", {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValueAngle}, -1), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValueAxis}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValueAngle(0), m_OutputValueAxis(0, 0, 0) {}

    WorkspaceNodeConvQuatToAngleAxis::WorkspaceNodeConvQuatToAngleAxis(const WorkspaceNodeConvQuatToAngleAxis& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValueAngle}, -1), WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValueAxis}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValueAngle(0), m_OutputValueAxis(0, 0, 0) {}

    void WorkspaceNodeConvQuatToAngleAxis::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValueAngle = glm::angle(*input0->Link->OutputPin.Output.Value.quat);
        m_OutputValueAxis  = glm::axis(*input0->Link->OutputPin.Output.Value.quat);
    }
}
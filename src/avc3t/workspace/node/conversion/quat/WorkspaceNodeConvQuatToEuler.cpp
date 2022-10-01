#include "WorkspaceNodeConvQuatToEuler.h"

namespace AVC3T {
    WorkspaceNodeConvQuatToEuler::WorkspaceNodeConvQuatToEuler() :
        WorkspaceNode("Quat -> Euler", {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z")},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0) {}

    WorkspaceNodeConvQuatToEuler::WorkspaceNodeConvQuatToEuler(const WorkspaceNodeConvQuatToEuler& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Quat)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z")},
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0) {}

    void WorkspaceNodeConvQuatToEuler::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        glm::vec3 euler = glm::eulerAngles(*input0->Link->OutputPin.Output.Value.quat);
        m_OutputValue0  = euler.x;
        m_OutputValue1  = euler.y;
        m_OutputValue2  = euler.z;
    }
}
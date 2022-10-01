#include "WorkspaceNodeConvVec3FloatToVec4.h"

namespace AVC3T {
    WorkspaceNodeConvVec3FloatToVec4::WorkspaceNodeConvVec3FloatToVec4() :
        WorkspaceNode("Vec3 + Float -> Vec4", {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Float, "w")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeConvVec3FloatToVec4::WorkspaceNodeConvVec3FloatToVec4(const WorkspaceNodeConvVec3FloatToVec4& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Float, "w")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeConvVec3FloatToVec4::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = glm::vec4(*input0->Link->OutputPin.Output.Value.vec3, *input1->Link->OutputPin.Output.Value.f);
    }
}
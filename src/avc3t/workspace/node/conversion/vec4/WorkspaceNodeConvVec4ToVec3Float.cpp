#include "WorkspaceNodeConvVec4ToVec3Float.h"

namespace AVC3T {
    WorkspaceNodeConvVec4ToVec3Float::WorkspaceNodeConvVec4ToVec3Float() :
        WorkspaceNode("Vec4 -> Vec3 + Float", {WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue0}, -1), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0) {}

    WorkspaceNodeConvVec4ToVec3Float::WorkspaceNodeConvVec4ToVec3Float(const WorkspaceNodeConvVec4ToVec3Float& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue0}, -1), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0) {}

    void WorkspaceNodeConvVec4ToVec3Float::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue0 = *input0->Link->OutputPin.Output.Value.vec4;
        m_OutputValue1 = input0->Link->OutputPin.Output.Value.vec4->w;
    }
}
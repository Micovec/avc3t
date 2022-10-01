#include "WorkspaceNodeConvVec3ToFloat.h"

namespace AVC3T {
    WorkspaceNodeConvVec3ToFloat::WorkspaceNodeConvVec3ToFloat() :
        WorkspaceNode("Vec3 -> 3x Float", {WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z")},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0) {}

    WorkspaceNodeConvVec3ToFloat::WorkspaceNodeConvVec3ToFloat(const WorkspaceNodeConvVec3ToFloat& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue0}, -1, "x"), WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue1}, -1, "y"),
                       WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue2}, -1, "z")},
                      other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue0(0), m_OutputValue1(0), m_OutputValue2(0) {}

    void WorkspaceNodeConvVec3ToFloat::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue0 = input0->Link->OutputPin.Output.Value.vec3->x;
        m_OutputValue1 = input0->Link->OutputPin.Output.Value.vec3->y;
        m_OutputValue2 = input0->Link->OutputPin.Output.Value.vec3->z;
    }
}
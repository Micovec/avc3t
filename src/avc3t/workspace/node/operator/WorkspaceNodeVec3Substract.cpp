#include "WorkspaceNodeVec3Substract.h"

namespace AVC3T {
    WorkspaceNodeVec3Substract::WorkspaceNodeVec3Substract() :
        WorkspaceNode("Vec3 - Vec3", {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeVec3Substract::WorkspaceNodeVec3Substract(const WorkspaceNodeVec3Substract& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec3), WorkspaceNodeInput(WorkspaceIOType_Vec3)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeVec3Substract::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = (*input0->Link->OutputPin.Output.Value.vec3) - (*input1->Link->OutputPin.Output.Value.vec3);
    }
}
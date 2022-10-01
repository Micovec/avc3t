#include "WorkspaceNodeVec3Mix.h"

namespace AVC3T {
    WorkspaceNodeVec3Mix::WorkspaceNodeVec3Mix() :
        WorkspaceNode("Mix Vec3",
                      {WorkspaceNodeInput(WorkspaceIOType_Vec3, "from"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeVec3Mix::WorkspaceNodeVec3Mix(const WorkspaceNodeVec3Mix& other) :
        WorkspaceNode(other.m_Title,
                      {WorkspaceNodeInput(WorkspaceIOType_Vec3, "from"), WorkspaceNodeInput(WorkspaceIOType_Vec3, "to"), WorkspaceNodeInput(WorkspaceIOType_Float, "t")},
                      {WorkspaceNodeOutput(WorkspaceIOType_Vec3, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeVec3Mix::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr)
            return;

        glm::vec3 from = *input0->Link->OutputPin.Output.Value.vec3;
        glm::vec3 to   = *input1->Link->OutputPin.Output.Value.vec3;
        float     t    = *input2->Link->OutputPin.Output.Value.f;

        m_OutputValue = from + (to - from) * t;
    }
}
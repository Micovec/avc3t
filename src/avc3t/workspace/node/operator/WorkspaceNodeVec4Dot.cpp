#include "WorkspaceNodeVec4Dot.h"

namespace AVC3T {
    WorkspaceNodeVec4Dot::WorkspaceNodeVec4Dot() :
        WorkspaceNode("Vec4 . Vec4", {WorkspaceNodeInput(WorkspaceIOType_Vec4), WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeVec4Dot::WorkspaceNodeVec4Dot(const WorkspaceNodeVec4Dot& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec4), WorkspaceNodeInput(WorkspaceIOType_Vec4)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeVec4Dot::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = glm::dot(*input0->Link->OutputPin.Output.Value.vec4, *input1->Link->OutputPin.Output.Value.vec4);
    }
}
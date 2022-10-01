#include "WorkspaceNodeVec4Normalize.h"

namespace AVC3T {
    WorkspaceNodeVec4Normalize::WorkspaceNodeVec4Normalize() :
        WorkspaceNode("Normalize Vec4", {WorkspaceNodeInput(WorkspaceIOType_Vec4)}, {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeVec4Normalize::WorkspaceNodeVec4Normalize(const WorkspaceNodeVec4Normalize& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Vec4)}, {WorkspaceNodeOutput(WorkspaceIOType_Vec4, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeVec4Normalize::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = glm::normalize(*input0->Link->OutputPin.Output.Value.vec4);
    }
}
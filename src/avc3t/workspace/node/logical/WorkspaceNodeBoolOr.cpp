#include "WorkspaceNodeBoolOr.h"

namespace AVC3T {
    WorkspaceNodeBoolOr::WorkspaceNodeBoolOr() :
        WorkspaceNode("Or", {WorkspaceNodeInput(WorkspaceIOType_Bool), WorkspaceNodeInput(WorkspaceIOType_Bool)}, {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue}, -1)},
                      {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(false) {}

    WorkspaceNodeBoolOr::WorkspaceNodeBoolOr(const WorkspaceNodeBoolOr& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Bool), WorkspaceNodeInput(WorkspaceIOType_Bool)},
                      {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(false) {}

    void WorkspaceNodeBoolOr::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link == nullptr || input1->Link == nullptr)
            return;

        m_OutputValue = *input0->Link->OutputPin.Output.Value.b || *input1->Link->OutputPin.Output.Value.b;
    }
}
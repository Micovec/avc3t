#include "WorkspaceNodeBoolNot.h"

namespace AVC3T {
    WorkspaceNodeBoolNot::WorkspaceNodeBoolNot() :
        WorkspaceNode("Not", {WorkspaceNodeInput(WorkspaceIOType_Bool)}, {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(false) {}

    WorkspaceNodeBoolNot::WorkspaceNodeBoolNot(const WorkspaceNodeBoolNot& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Bool)}, {WorkspaceNodeOutput(WorkspaceIOType_Bool, {&m_OutputValue}, -1)}, other.m_Style, other.m_BodySize,
                      other.m_Hint->GetHintText()),
        m_OutputValue(false) {}

    void WorkspaceNodeBoolNot::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = !(*input0->Link->OutputPin.Output.Value.b);
    }
}
#include "WorkspaceNodeSign.h"

namespace AVC3T {
    WorkspaceNodeSign::WorkspaceNodeSign() :
        WorkspaceNode("Sign", {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeSign::WorkspaceNodeSign(const WorkspaceNodeSign& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeSign::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        float val     = *input0->Link->OutputPin.Output.Value.f;
        m_OutputValue = val > 0 ? 1 : (val < 0 ? -1 : 0);
    }
}
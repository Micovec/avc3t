#include "WorkspaceNodeCos.h"

namespace AVC3T {
    WorkspaceNodeCos::WorkspaceNodeCos() :
        WorkspaceNode("Cos", {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeCos::WorkspaceNodeCos(const WorkspaceNodeCos& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeCos::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = std::cos(*input0->Link->OutputPin.Output.Value.f);
    }
}
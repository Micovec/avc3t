#include "WorkspaceNodeFloor.h"

namespace AVC3T {
    WorkspaceNodeFloor::WorkspaceNodeFloor() :
        WorkspaceNode("Floor", {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValue(0) {}

    WorkspaceNodeFloor::WorkspaceNodeFloor(const WorkspaceNodeFloor& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Float)}, {WorkspaceNodeOutput(WorkspaceIOType_Float, {&m_OutputValue}, -1)}, other.m_Style,
                      other.m_BodySize, other.m_Hint->GetHintText()),
        m_OutputValue(0) {}

    void WorkspaceNodeFloor::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];

        if (input0->Link == nullptr)
            return;

        m_OutputValue = std::floor(*input0->Link->OutputPin.Output.Value.f);
    }
}
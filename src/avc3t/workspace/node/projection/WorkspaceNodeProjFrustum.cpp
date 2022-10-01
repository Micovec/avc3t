#include "WorkspaceNodeProjFrustum.h"

namespace AVC3T {
    WorkspaceNodeProjFrustum::WorkspaceNodeProjFrustum() :
        WorkspaceNode("Frustum",
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Float, "left"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "right"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "bottom"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "top"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "near"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "far"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeProjFrustum::WorkspaceNodeProjFrustum(const WorkspaceNodeProjFrustum& other) :
        WorkspaceNode(other.m_Title,
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Float, "left"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "right"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "bottom"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "top"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "near"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "far"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeProjFrustum::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];
        std::shared_ptr<WorkspaceInputPin>& input3 = m_InputPins[3];
        std::shared_ptr<WorkspaceInputPin>& input4 = m_InputPins[4];
        std::shared_ptr<WorkspaceInputPin>& input5 = m_InputPins[5];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr || input3->Link == nullptr || input4->Link == nullptr || input5->Link == nullptr)
            return;

        m_Matrix = glm::frustum(*input0->Link->OutputPin.Output.Value.f, *input1->Link->OutputPin.Output.Value.f, *input2->Link->OutputPin.Output.Value.f,
                                *input3->Link->OutputPin.Output.Value.f, *input4->Link->OutputPin.Output.Value.f, *input5->Link->OutputPin.Output.Value.f);
    }
}
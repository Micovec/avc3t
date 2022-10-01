#include "WorkspaceNodeProjPerspective.h"

namespace AVC3T {
    WorkspaceNodeProjPerspective::WorkspaceNodeProjPerspective() :
        WorkspaceNode("Perspective",
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Float, "fov"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "aspect"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "near"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "far"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_Matrix(1.0f) {}

    WorkspaceNodeProjPerspective::WorkspaceNodeProjPerspective(const WorkspaceNodeProjPerspective& other) :
        WorkspaceNode(other.m_Title,
                      {
                          WorkspaceNodeInput(WorkspaceIOType_Float, "fov"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "aspect"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "near"),
                          WorkspaceNodeInput(WorkspaceIOType_Float, "far"),
                      },
                      {WorkspaceNodeOutput(WorkspaceIOType_Mat4, &m_Matrix, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()),
        m_Matrix(1.0f) {}

    void WorkspaceNodeProjPerspective::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];
        std::shared_ptr<WorkspaceInputPin>& input3 = m_InputPins[3];

        if (input0->Link == nullptr || input1->Link == nullptr || input2->Link == nullptr || input3->Link == nullptr)
            return;

        m_Matrix = glm::perspective(*input0->Link->OutputPin.Output.Value.f, *input1->Link->OutputPin.Output.Value.f, *input2->Link->OutputPin.Output.Value.f,
                                    *input3->Link->OutputPin.Output.Value.f);
    }
}
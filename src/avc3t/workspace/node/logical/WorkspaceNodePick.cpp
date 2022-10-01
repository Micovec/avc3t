#include "WorkspaceNodePick.h"

namespace AVC3T {
    WorkspaceNodePick::WorkspaceNodePick() :
        WorkspaceNode("Pick", {WorkspaceNodeInput(WorkspaceIOType_Bool), WorkspaceNodeInput(s_AllIOTypes, "if true"), WorkspaceNodeInput(s_AllIOTypes, "if false")},
                      {WorkspaceNodeOutput(s_AllIOTypes, {}, -1)}, {IM_COL32(190, 35, 52, 255)}),
        m_OutputValueBool(false) {
        m_OutputPins[0]->Output.Disabled = true;
    }

    WorkspaceNodePick::WorkspaceNodePick(const WorkspaceNodePick& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Bool), WorkspaceNodeInput(s_AllIOTypes, "if true"), WorkspaceNodeInput(s_AllIOTypes, "if false")},
                      {WorkspaceNodeOutput(s_AllIOTypes, {}, -1)}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()) {
        m_OutputPins[0]->Output.Disabled = true;
    }

    void WorkspaceNodePick::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];
        std::shared_ptr<WorkspaceInputPin>& input2 = m_InputPins[2];

        WorkspaceIOType input1Type = input1->Link == nullptr ? (input2->Link == nullptr ? s_AllIOTypes : input2->Link->OutputPin.Output.Type) : input1->Link->OutputPin.Output.Type;
        WorkspaceIOType input2Type = input2->Link == nullptr ? (input1->Link == nullptr ? s_AllIOTypes : input1->Link->OutputPin.Output.Type) : input2->Link->OutputPin.Output.Type;

        input1->Input.Type = input1Type;
        input2->Input.Type = input2Type;

        input1->Type = input1Type;
        input2->Type = input2Type;

        m_OutputPins[0]->Output.Disabled = true;
        m_OutputPins[0]->Output.Type = m_OutputPins[0]->Type = s_AllIOTypes;

        if (!input0->DataAvailable() || !input1->DataAvailable() || !input2->DataAvailable() || (input1->Link->OutputPin.Output.Type != input2->Link->OutputPin.Output.Type))
            return;

        WorkspaceIOType type  = input0->Link->OutputPin.Output.Type;
        bool            value = *input0->Link->OutputPin.Output.Value.b;

        switch (type) {
            case WorkspaceIOType_Bool: m_OutputPins[0]->Output.Value.b = value ? input1->Link->OutputPin.Output.Value.b : input2->Link->OutputPin.Output.Value.b; break;

            case WorkspaceIOType_Float: m_OutputPins[0]->Output.Value.f = value ? input1->Link->OutputPin.Output.Value.f : input2->Link->OutputPin.Output.Value.f; break;

            case WorkspaceIOType_Vec3: m_OutputPins[0]->Output.Value.vec3 = value ? input1->Link->OutputPin.Output.Value.vec3 : input2->Link->OutputPin.Output.Value.vec3; break;

            case WorkspaceIOType_Vec4: m_OutputPins[0]->Output.Value.vec4 = value ? input1->Link->OutputPin.Output.Value.vec4 : input2->Link->OutputPin.Output.Value.vec4; break;

            case WorkspaceIOType_Mat4: m_OutputPins[0]->Output.Value.mat4 = value ? input1->Link->OutputPin.Output.Value.mat4 : input2->Link->OutputPin.Output.Value.mat4; break;

            case WorkspaceIOType_Quat: m_OutputPins[0]->Output.Value.quat = value ? input1->Link->OutputPin.Output.Value.quat : input2->Link->OutputPin.Output.Value.quat; break;

            default:
                // Should not happen
                break;
        }

        m_OutputPins[0]->Output.Type     = input1Type;
        m_OutputPins[0]->Type            = input1Type;
        m_OutputPins[0]->Output.Disabled = false;
    }
}
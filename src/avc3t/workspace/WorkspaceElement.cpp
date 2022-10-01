#include "WorkspaceElement.h"
#include "WorkspaceRenderContext.h"
#include "imgui.h"

namespace AVC3T {
    void WorkspaceElement::RenderChildren(WorkspaceRenderContext& context) {
        for (auto&& child : m_Children) {
            child->Render(context);
        }
    }

    // Position is relative to node position
    WorkspaceMouseInteractionResult WorkspaceElement::MousePressed(const WorkspaceMouseInteraction& interaction) {
        for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it) {
            auto&&                          child = *it;

            WorkspaceMouseInteractionResult result =
                child->MousePressed(WorkspaceMouseInteraction(interaction, GetRelativePosition(interaction.mousePosition, child->GetPosition())));
            if (!interaction.Handled && result.Type != InteractedElementType_None)
                return result;
        }

        return WorkspaceMouseInteractionResult();
    }

    // Position is relative to node position
    WorkspaceMouseInteractionResult WorkspaceElement::MouseClicked(const WorkspaceMouseInteraction& interaction) {
        for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it) {
            auto&&                          child = *it;
            WorkspaceMouseInteractionResult result =
                child->MouseClicked(WorkspaceMouseInteraction(interaction, GetRelativePosition(interaction.mousePosition, child->GetPosition())));
            if (!interaction.Handled && result.Type != InteractedElementType_None)
                return result;
        }

        return WorkspaceMouseInteractionResult();
    }

    // Position is relative to node position
    WorkspaceMouseInteractionResult WorkspaceElement::MouseReleased(const WorkspaceMouseInteraction& interaction) {
        for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it) {
            auto&&                          child = *it;
            WorkspaceMouseInteractionResult result =
                child->MouseReleased(WorkspaceMouseInteraction(interaction, GetRelativePosition(interaction.mousePosition, child->GetPosition())));
            if (!interaction.Handled && result.Type != InteractedElementType_None)
                return result;
        }

        return WorkspaceMouseInteractionResult();
    }

    // Position is relative to node position
    WorkspaceMouseInteractionResult WorkspaceElement::MousePositionUpdate(const WorkspaceMouseInteraction& interaction) {
        for (auto it = m_Children.rbegin(); it != m_Children.rend(); ++it) {
            auto&&                          child = *it;
            WorkspaceMouseInteractionResult result =
                child->MousePositionUpdate(WorkspaceMouseInteraction(interaction, GetRelativePosition(interaction.mousePosition, child->GetPosition())));
            if (!interaction.Handled && result.Type != InteractedElementType_None)
                return result;
        }

        return WorkspaceMouseInteractionResult();
    }

    ImVec2 WorkspaceElement::GetAbsolutePosition(const WorkspaceRenderContext& context) const {
        return ImVec2(context.Origin.x + m_Position.x, context.Origin.y + m_Position.y);
    }

    ImVec2 WorkspaceElement::GetAbsolutePosition() const {
        ImVec2            position = m_Position;

        WorkspaceElement* parent = m_Parent;
        while (parent != nullptr) {
            position.x += parent->m_Position.x;
            position.y += parent->m_Position.y;

            parent = parent->m_Parent;
        }

        return position;
    }
} // namespace AVC3T
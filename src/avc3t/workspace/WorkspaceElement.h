#pragma once

#include <vector>

#include "../ui/MouseButton.h"
#include "../utils/ImGuiUtils.h"
#include "WorkspaceMouseInteraction.h"
#include "WorkspaceMouseInteractionResult.h"
#include "WorkspaceRenderContext.h"

namespace AVC3T {
    class WorkspaceElement {
      public:
        WorkspaceElement() : m_Parent(nullptr), m_Position(0, 0), m_Size(0, 0), m_Flags(WorkspaceInteractionFlags_None), /*m_Parent(parent),*/ m_Children() {}

        WorkspaceElement(const WorkspaceElement& other) : m_Position(other.m_Position), m_Size(other.m_Size), m_Flags(other.m_Flags), /*m_Parent(nullptr),*/ m_Children() {}

        virtual ~WorkspaceElement() {}

        virtual void Render(WorkspaceRenderContext& context) = 0;
        virtual void Evaluate(double ts) {}

        void         SetParent(WorkspaceElement* parentr) {
            m_Parent = parentr;
        }

        WorkspaceElement* GetParent() {
            return m_Parent;
        }

        const WorkspaceElement* GetParent() const {
            return m_Parent;
        }

        const ImVec2& GetSize() const {
            return m_Size;
        }

        virtual void SetPosition(const ImVec2& position) {
            m_Position = position;
        }
        const ImVec2& GetPosition() const {
            return m_Position;
        }

        ImVec2      GetAbsolutePosition(const WorkspaceRenderContext& context) const;
        ImVec2      GetAbsolutePosition() const;

        inline void AddFlags(WorkspaceInteractionFlags flags) {
            m_Flags |= flags;
        }
        inline void SetFlags(WorkspaceInteractionFlags flags) {
            m_Flags = flags;
        }
        inline void RemoveFlags(WorkspaceInteractionFlags flags) {
            m_Flags &= ~flags;
        }
        inline bool HasFlags(WorkspaceInteractionFlags flags) const {
            return m_Flags & flags;
        }
        WorkspaceInteractionFlags GetFlags() const {
            return m_Flags;
        }

        // Cursor handling
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction);
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction);
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MouseReleased(const WorkspaceMouseInteraction& interaction);
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction);

      protected:
        void RenderChildren(WorkspaceRenderContext& context);

      protected:
        WorkspaceElement*         m_Parent;
        ImVec2                    m_Position;
        ImVec2                    m_Size;

        WorkspaceInteractionFlags m_Flags;
        // TODO try to move elements to stack instead
        std::vector<std::shared_ptr<WorkspaceElement>> m_Children;
    };
}
#pragma once

#include <imgui/imgui.h>

#include "EditTextPopup.h"
#include "ScenePanel.h"
#include "../workspace/Workspace.h"

namespace AVC3T {
    class WorkspacePanel {
      public:
        WorkspacePanel(const std::shared_ptr<ScenePanel>& scenePanel);

        void       Render();
        void       Update(double ts);

        Workspace& GetWorkspace() {
            return m_Workspace;
        }

      private:
        bool        HandleCursorWorkspaceInteraction();
        void        ShowContextMenu(const ImVec2& mousePos);
        void        ShowWorkspaceContextMenu(const ImVec2& mousePos);
        void        ShowNodeContextMenu(const ImVec2& mousePos, WorkspaceNode* node, std::vector<WorkspaceMouseInteractionOption>& additionalOptions);
        void        ShowInputPinContextMenu(const ImVec2& mousePos, WorkspaceInputPin* pin);
        void        ShowOutputPinContextMenu(const ImVec2& mousePos, WorkspaceOutputPin* pin);
        void        ShowLinkContextMenu(const ImVec2& mousePos, WorkspaceLink* link);

        inline bool IsMouseInsideWorkspace();

      private:
        std::shared_ptr<ScenePanel>     m_ScenePanel;
        EditTextPopup                   m_EditTextPopup;

        Workspace                       m_Workspace;

        bool                            m_IsContextMenuShown = false;
        WorkspaceMouseInteractionResult m_MouseInteractionResult;
    };
}
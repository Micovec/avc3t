#pragma once

#include <memory>

#include "ui/MainMenuBar.h"
#include "ui/ScenePanel.h"
#include "ui/WorkspacePanel.h"

namespace AVC3T {
    class Application {
      public:
        Application();

        void Init();
        void Deinit();
        void Render();
        void Update(double ts);

      private:
        std::shared_ptr<ScenePanel>     m_ScenePanel;
        std::shared_ptr<WorkspacePanel> m_WorkspacePanel;
        std::shared_ptr<MainMenuBar>    m_MainMenuBar;

        ImGuiDockNodeFlags              m_DockSpaceFlags;
    };
}
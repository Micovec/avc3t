#pragma once

#include "../workspace/Workspace.h"

namespace AVC3T {
    class MainMenuBar {
      public:
        MainMenuBar(Workspace& workspace, Scene& scene);

        void Render();

      private:
        void Open();
        void Save();

        void ShowExceptionThrown();

      private:
        Workspace&  m_Workspace;
        Scene&      m_Scene;

        bool        m_ExceptionThrown;
        std::string m_ExceptionMessage;
    };
}
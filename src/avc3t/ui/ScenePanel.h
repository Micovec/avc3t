#pragma once

#include "../scene/Scene.h"
#include "../render/FrameBufferObject.h"

namespace AVC3T {
    class ScenePanel {
      public:
        ScenePanel();

        void   Render();
        void   Update(double ts);

        void   AddObject(const std::shared_ptr<SceneObject>& object);
        void   RemoveObject(const std::shared_ptr<SceneObject>& object);

        Scene& GetScene() {
            return m_Scene;
        }

      private:
        void        HandleCursorInteraction();
        void        ShowContextMenu();

        inline bool IsMouseInsideWorkspace();

      private:
        static const std::size_t RENDER_WIDTH = 1600, RENDER_HEIGHT = 900;

        bool                     m_IsContextMenuShown;
        ImVec2                   m_MouseDownPos;

        ImVec2                   m_TopLeft;
        ImVec2                   m_PanelSize;

        EditorCamera             m_Camera;
        Scene                    m_Scene;
        FrameBufferObject        m_FrameBufferObject;
    };
}
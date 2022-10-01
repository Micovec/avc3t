#include "ScenePanel.h"

#include <imgui/imgui.h>

namespace AVC3T {
    ScenePanel::ScenePanel() : m_IsContextMenuShown(false), m_TopLeft(), m_PanelSize(), m_Camera(70, 1, 40), m_Scene(), m_FrameBufferObject(RENDER_WIDTH, RENDER_HEIGHT) {}

    void ScenePanel::Render() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Scene");
        ImGui::PopStyleVar(); // Pop window padding

        m_FrameBufferObject.Bind();

        m_TopLeft   = ImGui::GetCursorScreenPos();
        m_PanelSize = ImGui::GetContentRegionAvail();

        m_Camera.SetAspect(m_PanelSize.x / m_PanelSize.y);

        m_Scene.EnableCameras();

        // Render scene into texture
        m_Scene.Render({m_PanelSize.x, m_PanelSize.y}, &m_Camera);
        ImGui::Image((ImTextureID)m_FrameBufferObject.GetTextureID(), m_PanelSize, ImVec2(0, 1), ImVec2(1, 0));

        m_Scene.DisableCameras();

        m_FrameBufferObject.Unbind();

        if (IsMouseInsideWorkspace()) {
            //ImGui::PushStyleVar
            HandleCursorInteraction();
            m_Camera.Update();
        }

        ImGui::End();
    }

    void ScenePanel::AddObject(const std::shared_ptr<SceneObject>& sceneObject) {
        m_Scene.AddObject(sceneObject);
    }

    void ScenePanel::RemoveObject(const std::shared_ptr<SceneObject>& sceneObject) {
        m_Scene.RemoveObject(sceneObject);
    }

    void ScenePanel::Update(double ts) {}

    void ScenePanel::HandleCursorInteraction() {
        ImVec2 mousePosition = ImGui::GetMousePos();

        if (m_IsContextMenuShown)
            ShowContextMenu();

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (!ImGui::IsAnyItemHovered())
                m_IsContextMenuShown = false;
        }

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
            m_MouseDownPos = mousePosition;
        }

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Right)) {
            if (m_MouseDownPos.x != -FLT_MAX && m_MouseDownPos.y != +FLT_MAX && m_MouseDownPos.x == mousePosition.x && m_MouseDownPos.y == mousePosition.y) {
                m_IsContextMenuShown = true;
            }
        }
    }

    void ScenePanel::ShowContextMenu() {
        ImGui::OpenPopup("scenePopupContextMenu");

        if (ImGui::BeginPopup("scenePopupContextMenu")) {
            if (ImGui::Selectable("Center camera to origin")) {
                m_Camera.SetLookAt(glm::vec3(0, 0, 0));
                m_IsContextMenuShown = false;
            }

            if (ImGui::Selectable("Reset camera")) {
                m_Camera.Reset();
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    bool ScenePanel::IsMouseInsideWorkspace() {
        ImVec2 mousePosition = ImGui::GetMousePos();
        ImVec2 bottomRight(m_TopLeft.x + m_PanelSize.y, m_TopLeft.y + m_PanelSize.y);

        return (ImGui::IsWindowHovered() || m_IsContextMenuShown) && mousePosition.x >= m_TopLeft.x && mousePosition.y >= m_TopLeft.y && mousePosition.x <= bottomRight.x &&
            mousePosition.y <= bottomRight.y;
    }
}
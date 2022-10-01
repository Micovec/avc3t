#include "Application.h"

#include <imgui/imgui_internal.h>

#include "library/SceneObjectLibrary.h"
#include "library/ShaderLibrary.h"
#include "library/TextureLibrary.h"

#include "ui/TextPopupModal.h"

namespace AVC3T {
    Application::Application() :
        m_ScenePanel(std::make_shared<ScenePanel>()), m_WorkspacePanel(std::make_shared<WorkspacePanel>(m_ScenePanel)),
        m_MainMenuBar(std::make_shared<MainMenuBar>(m_WorkspacePanel->GetWorkspace(), m_ScenePanel->GetScene())), m_DockSpaceFlags(ImGuiDockNodeFlags_None) {}

    void Application::Init() {
        SceneObjectLibrary::Init();
        ShaderLibrary::Init();
    }

    void Application::Deinit() {
        SceneObjectLibrary::Deinit();
        ShaderLibrary::Deinit();
        TextureLibrary::FreeTextures();

        m_ScenePanel.reset();
        m_WorkspacePanel.reset();
    }

    void Application::Render() {
        // TODO: clean up unnecessary flags
        const ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDocking |
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

        ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, windowFlags);
        ImGui::PopStyleVar(); // Pop window padding

        // Submit the DockSpace
        ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");
        if (!ImGui::DockBuilderGetNode(dockspaceID)) {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, m_DockSpaceFlags);

            ImGuiID dock_main_id  = dockspaceID;
            ImGuiID dock_right_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.5f, nullptr, &dock_main_id);

            // TODO: get window names from panels
            ImGui::DockBuilderDockWindow("Scene", dock_right_id);
            ImGui::DockBuilderDockWindow("Workspace", dock_main_id);

            ImGui::DockBuilderFinish(dock_main_id);
        }

        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), m_DockSpaceFlags);

        m_ScenePanel->Render();

        m_WorkspacePanel->Render();
        m_MainMenuBar->Render();

        TextPopupModal::Render();

        ImGui::End();
    }

    void Application::Update(double ts) {
        m_WorkspacePanel->Update(ts);
        m_ScenePanel->Update(ts);
    }
}
#include "MainMenuBar.h"

#include <fstream>
#include <imgui/imgui.h>
#ifndef __EMSCRIPTEN__
#include <nfd.h>
#endif

#include "../serialization/Deserializer.h"
#include "../serialization/Serializer.h"
#include "../utils/ID.h"

namespace AVC3T {
    MainMenuBar::MainMenuBar(Workspace& workspace, Scene& scene) : m_Workspace(workspace), m_Scene(scene), m_ExceptionThrown(false), m_ExceptionMessage() {}

    void MainMenuBar::Render() {
        if (ImGui::BeginMainMenuBar()) {
#ifndef __EMSCRIPTEN__
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open")) {
                    Open();
                }
                if (ImGui::MenuItem("Save")) {
                    Save();
                }
                ImGui::EndMenu();
            }
#endif

            if (ImGui::BeginMenu("Time")) {
                if (ImGui::MenuItem("Resume"))
                    m_Workspace.GetTime().Resume();
                if (ImGui::MenuItem("Pause"))
                    m_Workspace.GetTime().Pause();

                ImGui::Separator();

                if (ImGui::MenuItem("Reset"))
                    m_Workspace.GetTime().Reset();

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (m_ExceptionThrown) {
            ShowExceptionThrown();
        }
    }

    void MainMenuBar::Open() {
#ifndef __EMSCRIPTEN__
        NFD_Init();

        nfdchar_t*            outPath = nullptr;

        nfdu8filteritem_t     filters[1] = {{"AVC3T", "avc3t"}};
        nfdopendialogu8args_t args       = {0};
        args.filterList                  = filters;
        args.filterCount                 = 1;

        nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);

        if (result == NFD_OKAY) {
            m_Workspace.Clear();
            m_Workspace.ResetScrolling();
            ID::Reset();

            Serializer ser;
            try {
                std::ifstream stream(outPath);
                ser.Serialize(m_Workspace, m_Scene, stream);
            } catch (const std::exception& e) {
                m_ExceptionThrown  = true;
                m_ExceptionMessage = e.what();
            } catch (...) {
                m_ExceptionThrown  = true;
                m_ExceptionMessage = "Unknown exception";
            }
        }

        NFD_Quit();
#endif
    }

    void MainMenuBar::Save() {
#ifndef __EMSCRIPTEN__
        nfdchar_t*            outPath = nullptr;

        nfdu8filteritem_t     filters[1] = {{"AVC3T", "avc3t"}};
        nfdsavedialogu8args_t args       = {0};
        args.filterList                  = filters;
        args.filterCount                 = 1;

        nfdresult_t result = NFD_SaveDialogU8_With(&outPath, &args);

        if (result == NFD_OKAY) {
            Deserializer des;

            try {
                std::ofstream stream(outPath);
                des.Deserialize(m_Workspace, stream, Deserializer::Format::Text);
            } catch (const std::exception& e) {
                m_ExceptionThrown  = true;
                m_ExceptionMessage = e.what();
            } catch (...) {
                m_ExceptionThrown  = true;
                m_ExceptionMessage = "Unknown exception";
            }
        }
#endif
    }

    void MainMenuBar::ShowExceptionThrown() {
        ImGui::OpenPopup("Exception thrown");
        if (ImGui::BeginPopupModal("Exception thrown", &m_ExceptionThrown, ImGuiWindowFlags_AlwaysAutoResize)) {
            std::string message = "An exception has been thrown: ";
            message += m_ExceptionMessage;

            ImGui::TextUnformatted(message.data());
            ImGui::EndPopup();
        }
    }
} // namespace AVC3T
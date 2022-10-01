#include "TextPopupModal.h"

#include <imgui/imgui.h>

namespace AVC3T {
    TextPopupModal::TextPopupModal() : m_IsOpen(false), m_Title(nullptr), m_Text(nullptr) {}

    void TextPopupModal::Render() {
        TextPopupModal& instance = GetIntance();

        if (!instance.m_IsOpen)
            return;

        ImGui::OpenPopup(instance.m_Title);
        if (ImGui::BeginPopupModal(instance.m_Title, &instance.m_IsOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text(instance.m_Text);
            ImGui::EndPopup();
        }
    }

    void TextPopupModal::Open(const char* title, const char* text) {
        TextPopupModal& instance = GetIntance();

        instance.m_Title  = title;
        instance.m_Text   = text;
        instance.m_IsOpen = true;
    }

    TextPopupModal& TextPopupModal::GetIntance() {
        static TextPopupModal instance;
        return instance;
    }
}
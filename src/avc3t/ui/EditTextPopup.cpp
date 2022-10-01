#include "EditTextPopup.h"
#include "misc/cpp/imgui_stdlib.h"

namespace AVC3T {
    EditTextPopup::EditTextPopup() : m_IsOpen(false), m_Title(), m_Text(nullptr) {}

    void EditTextPopup::Open(const std::string_view title, std::string& text) {
        m_IsOpen = true;
        m_Title  = title;
        m_Text   = &text;
    }

    void EditTextPopup::Render() {
        if (!m_IsOpen)
            return;

        ImGui::OpenPopup(m_Title.data());

        if (ImGui::BeginPopupModal(m_Title.data(), &m_IsOpen, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::InputTextMultiline("##editText", m_Text);
            ImGui::EndPopup();
        }
    }
}
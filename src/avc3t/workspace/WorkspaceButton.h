#pragma once

#include "../utils/ID.h"

#include "WorkspaceElement.h"

namespace AVC3T {
    typedef void (*WorkspaceButtonCallback)(void* userData);

    class WorkspaceButton : public WorkspaceElement {
      public:
        WorkspaceButton(std::string_view text, WorkspaceButtonCallback callback = 0, void* userData = nullptr) :
            WorkspaceElement(), m_Text(text), m_Id(ID::Generate()), m_Callback(callback), m_UserData(userData) {
            if (m_Text.empty()) {
                m_Size.x = m_Size.y = 0;
                return;
            }

            ImVec2            textSize = ImGui::CalcTextSize(m_Text.c_str());

            const ImGuiStyle& style = ImGui::GetStyle();
            m_Size.x                = textSize.x + style.FramePadding.y * 2.0f;
            m_Size.y                = textSize.y + style.FramePadding.x * 2.0f;
        }

        ImVec2 GetButtonSize() const {
            ImVec2            labelSize = ImGui::CalcTextSize(m_Text.c_str());

            const ImGuiStyle& style = ImGui::GetStyle();
            ImVec2            size  = ImVec2(labelSize.x + style.FramePadding.x * 2.0f, labelSize.y + style.FramePadding.y * 2.0f);

            return size;
        }

        std::string_view GetText() const {
            return m_Text;
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2      cursorPosition = GetAbsolutePosition(context);

            std::string buttonText = m_Text;
            buttonText += "##" + std::to_string(m_Id);

            if (context.DrawList->AddButton(cursorPosition, buttonText) && m_Callback != 0)
                m_Callback(m_UserData);
        }

        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction) override {
            return GetGeneralInteractionResult(interaction);
        }

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            return GetGeneralInteractionResult(interaction);
        }

        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override {
            return GetGeneralInteractionResult(interaction);
        }

        virtual WorkspaceMouseInteractionResult MouseReleased(const WorkspaceMouseInteraction& interaction) override {
            return GetGeneralInteractionResult(interaction);
        }

      protected:
        virtual WorkspaceMouseInteractionResult GetGeneralInteractionResult(const WorkspaceMouseInteraction& interaction) {
            if (m_Size.x > 0 && IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), GetButtonSize()))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Input);

            return WorkspaceMouseInteractionResult();
        }

      protected:
        std::string             m_Text;
        std::size_t             m_Id;
        WorkspaceButtonCallback m_Callback;
        void*                   m_UserData;
    };
} // namespace AVC3T
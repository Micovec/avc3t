#pragma once

#include "WorkspaceButton.h"

namespace AVC3T {
    class WorkspaceHint : public WorkspaceButton {
      public:
        WorkspaceHint(const std::string_view& text) : WorkspaceButton(s_ButtonText), m_HintText(text), m_Shown(false) {}

        virtual void Render(WorkspaceRenderContext& context) override {
            if (m_HintText.empty())
                return;

            ImVec2 cursorPosition = GetAbsolutePosition(context);
            cursorPosition.x += context.Origin.x;
            cursorPosition.y += context.Origin.y;

            if (m_Shown)
                context.DrawList->PushStyleColor(ImGuiCol_Button, s_ButtonColorActive);
            else
                context.DrawList->PushStyleColor(ImGuiCol_Button, s_ButtonColor);

            context.DrawList->PushStyleColor(ImGuiCol_ButtonActive, s_ButtonColorActive);
            context.DrawList->PushStyleColor(ImGuiCol_ButtonHovered, s_ButtonColorHovered);

            std::string buttonText = m_Text;
            buttonText += "##" + std::to_string(m_Id);

            if (context.DrawList->AddButton(cursorPosition, buttonText))
                m_Shown = !m_Shown;

            context.DrawList->PopStyleColor();
            context.DrawList->PopStyleColor();
            context.DrawList->PopStyleColor();

            if (!m_Shown)
                return;

            DrawHint(context);
        }

        void Show() {
            m_Shown = true;
        }

        const std::string_view& GetHintText() const {
            return m_HintText;
        }

      protected:
        void DrawHint(WorkspaceRenderContext& context) {
            ImVec2 max = GetAbsolutePosition(context);
            max.x += context.Origin.x;
            max.y += context.Origin.y - s_PopupDistance;

            ImVec2 min = max;
            min.x -= m_Size.x;
            min.y -= m_Size.y;

            context.DrawList->AddRectFilled(min, max, s_BackgroundColor, 0, 0, s_ZIndex);

            ImVec2 textPosition = min;
            textPosition.x += s_Padding.x;
            textPosition.y += s_Padding.y;

            context.DrawList->AddText(textPosition, IM_COL32(255, 255, 255, 255), m_HintText.data(), s_ZIndex);
        }

        virtual WorkspaceMouseInteractionResult GetGeneralInteractionResult(const WorkspaceMouseInteraction& interaction) override {
            if (m_HintText.empty())
                return WorkspaceMouseInteractionResult();

            return WorkspaceButton::GetGeneralInteractionResult(interaction);
        }

      protected:
        static constexpr ImVec4      s_Padding         = ImVec4(8, 8, 8, 8);
        static constexpr float       s_PopupDistance   = 15.f;
        static constexpr ImU32       s_BackgroundColor = IM_COL32(150, 150, 150, 255);

        static constexpr ImU32       s_ButtonColor        = IM_COL32(17, 80, 180, 180);
        static constexpr ImU32       s_ButtonColorActive  = IM_COL32(17, 106, 221, 255);
        static constexpr ImU32       s_ButtonColorHovered = IM_COL32(17, 106, 221, 215);

        static constexpr int         s_ZIndex     = 1000;
        static constexpr const char* s_ButtonText = "?";

        std::string_view             m_HintText;
        bool                         m_Shown;
    };
}
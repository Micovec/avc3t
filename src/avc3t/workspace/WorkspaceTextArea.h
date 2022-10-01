#pragma once

#include "WorkspaceElement.h"

namespace AVC3T {
    class WorkspaceTextArea : public WorkspaceElement {

      public:
        WorkspaceTextArea(std::size_t id, bool multiline, bool autoResize, ImGuiInputTextCallback callback = 0, void* data = nullptr) :
            WorkspaceElement(), m_Id(id), m_Text(), m_Multiline(multiline), m_AutoResize(autoResize), m_MaxSize(-1, -1), m_UserData(autoResize, &m_Text, callback),
            m_Callback(callback), m_Data(data) {}

        void Render(WorkspaceRenderContext& context) override {
            ImVec2      position = GetAbsolutePosition(context);

            std::string textAreaId = "##valueTextArea" + std::to_string(m_Id);
            context.DrawList->AddTextArea(position, textAreaId, m_Multiline, &m_Text, m_Size, &WorkspaceTextArea::TextCallback, &m_UserData);
        }

        const std::string& GetText() const {
            return m_Text;
        }

        void SetSize(const ImVec2& size) {
            m_Size = size;
        }
        void SetText(const std::string& text) {
            m_Text = text;
        }

        bool IsMultiline() const {
            return m_Multiline;
        }

        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override {
            if (interaction.mouseButton == MouseButton::Left && IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), GetSize()))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Input);

            return WorkspaceElement::MousePressed(interaction);
        }

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), GetSize()))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Input);

            return WorkspaceElement::MousePositionUpdate(interaction);
        }

      private:
        struct TextAreaCallbackData {
            TextAreaCallbackData(bool canResize, std::string* text, ImGuiInputTextCallback callback, void* data = nullptr) :
                CanResize(canResize), Text(text), Callback(callback), Data(data) {}

            bool                   CanResize;
            std::string*           Text;
            ImGuiInputTextCallback Callback;
            void*                  Data;
        };

      private:
        static int TextCallback(ImGuiInputTextCallbackData* data) {
            TextAreaCallbackData* userData = static_cast<TextAreaCallbackData*>(data->UserData);

            if (data->EventFlag & ImGuiInputTextFlags_CallbackResize && userData->CanResize && ((size_t)data->BufTextLen) >= userData->Text->capacity()) {
                userData->Text->reserve(std::max(userData->Text->capacity() * 2, static_cast<std::size_t>(data->BufTextLen + 1)));
                data->Buf = userData->Text->data();
            }

            if (data->EventFlag & ImGuiInputTextFlags_CallbackAlways) {
                userData->Text->clear();
                for (int i = 0; i < data->BufTextLen; ++i)
                    userData->Text->push_back(data->Buf[i]);
            }

            if (userData->Callback) {
                ImGuiInputTextCallbackData newData = *data;
                newData.UserData                   = userData->Data;

                return userData->Callback(&newData);
            }

            return 0;
        }

      protected:
        std::size_t            m_Id;
        std::string            m_Text;
        bool                   m_Multiline;
        bool                   m_AutoResize;
        ImVec2                 m_MaxSize;
        TextAreaCallbackData   m_UserData;

        ImGuiInputTextCallback m_Callback;
        void*                  m_Data;
    };
} // namespace AVC3T
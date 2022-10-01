#pragma once

#include <imgui.h>
#include <string>

namespace AVC3T {
    class EditTextPopup {
      public:
        EditTextPopup();

        void Open(const std::string_view title, std::string& string);
        void Render();

        bool IsOpen() const {
            return m_IsOpen;
        }

      private:
        static int InputTextCallback(ImGuiInputTextCallbackData* data);

      private:
        bool             m_IsOpen;
        std::string_view m_Title;
        std::string*     m_Text;
    };
}
#pragma once

namespace AVC3T {
    class TextPopupModal {
      public:
        static void Render();
        static void Open(const char* title, const char* text);

      private:
        bool        m_IsOpen;
        const char* m_Title;
        const char* m_Text;

      private:
        TextPopupModal();

        static TextPopupModal& GetIntance();
    };
}
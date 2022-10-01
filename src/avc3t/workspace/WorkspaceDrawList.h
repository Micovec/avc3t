#pragma once

#include <map>
#include <queue>
#include <string>

#include "imgui/imgui.h"

namespace AVC3T {
    struct BezierCubic {
        BezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int numSegments) :
            P1(p1), P2(p2), P3(p3), P4(p4), Color(col), Thickness(thickness), NumSegments(numSegments) {}

        const ImVec2 P1;
        const ImVec2 P2;
        const ImVec2 P3;
        const ImVec2 P4;
        const ImU32  Color;
        const float  Thickness;
        const int    NumSegments;
    };

    struct CircleFilled {
        CircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments) : Center(center), Radius(radius), Color(col), NumSegments(num_segments) {}

        const ImVec2 Center;
        const float  Radius;
        const ImU32  Color;
        const int    NumSegments;
    };

    struct CircleFilledColors {
        CircleFilledColors(const ImVec2& center, float radius, std::vector<ImU32> colors, int num_segments) :
            Center(center), Radius(radius), Colors(colors), NumSegments(num_segments) {}

        const ImVec2             Center;
        const float              Radius;
        const std::vector<ImU32> Colors;
        const int                NumSegments;
    };

    struct Line {
        Line(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f) : P1(p1), P2(p2), Color(col), Thickness(thickness) {}

        const ImVec2 P1;
        const ImVec2 P2;
        const ImU32  Color;
        const float  Thickness;
    };

    struct Rect {
        Rect(const ImVec2& pMin, const ImVec2& pMax, ImU32 col, float rounding, ImDrawFlags flags, float thickness) :
            PMin(pMin), PMax(pMax), Color(col), Rounding(rounding), Flags(flags), Thickness(thickness) {}

        const ImVec2      PMin;
        const ImVec2      PMax;
        const ImU32       Color;
        const float       Rounding;
        const ImDrawFlags Flags;
        const float       Thickness;
    };

    struct RectFilled {
        RectFilled(const ImVec2& pMin, const ImVec2& pMax, ImU32 col, float rounding, ImDrawFlags flags) : PMin(pMin), PMax(pMax), Color(col), Rounding(rounding), Flags(flags) {}

        const ImVec2      PMin;
        const ImVec2      PMax;
        const ImU32       Color;
        const float       Rounding;
        const ImDrawFlags Flags;
    };

    struct Text {
        Text(const ImVec2& pos, ImU32 col, const char* text) : Position(pos), Color(col), SText(text) {}

        const ImVec2      Position;
        const ImU32       Color;
        const std::string SText;
    };

    struct TextArea {
        TextArea(const ImVec2& position, std::string_view label, bool multiline, std::string* text, ImVec2 size, ImGuiInputTextCallback callback, void* userData) :
            Position(position), Label(label), Multiline(multiline), Text(text), Size(size), Callback(callback), UserData(userData) {}

        const ImVec2           Position;
        const std::string      Label;
        const bool             Multiline;
        std::string*           Text;
        const ImVec2           Size;
        ImGuiInputTextCallback Callback;
        void*                  UserData;
    };

    struct TriangleFilled {
        TriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col) : P1(p1), P2(p2), P3(p3), Color(col) {}

        const ImVec2 P1;
        const ImVec2 P2;
        const ImVec2 P3;
        const ImU32  Color;
    };

    struct DragFloat {
        DragFloat(const ImVec2& position, const std::string& id, float* value, bool disabled, float width) :
            Position(position), Id(id), Value(value), Disabled(disabled), Width(width) {}

        const ImVec2      Position;
        const std::string Id;
        float*            Value;
        const bool        Disabled;
        const float       Width;
    };

    struct Button {
        Button(const ImVec2& position, const std::string& label) : Position(position), Label(label) {}

        const ImVec2      Position;
        const std::string Label;
    };

    struct Checkbox {
        Checkbox(const ImVec2& position, const std::string& label, bool* value, bool disabled) : Position(position), Label(label), Value(value), Disabled(disabled) {}

        const ImVec2      Position;
        const std::string Label;
        bool*             Value;
        bool              Disabled;
    };

    struct Image {
        Image(const ImVec2& position, ImTextureID textureID, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tintCol, const ImVec4& borderCol) :
            Position(position), TextureId(textureID), Size(size), UV0(uv0), UV1(uv1), TintColor(tintCol), BorderColor(borderCol) {}

        const ImVec2      Position;
        const ImTextureID TextureId;
        const ImVec2      Size;
        const ImVec2      UV0;
        const ImVec2      UV1;
        const ImVec4      TintColor;
        const ImVec4      BorderColor;
    };

    struct StyleColor {
        StyleColor(ImGuiCol idx, ImU32 col) : Index(idx), Color(col) {}

        const ImGuiCol Index;
        const ImU32    Color;
    };

    enum class InstructionType {
        // Drawable
        BezierCubic,
        CircleFilled,
        CircleFilledColors,
        Rect,
        RectFilled,
        Line,
        TriangleFilled,

        // Input
        Button,
        Checkbox,
        DragFloat,
        Image,
        Text,
        TextArea,

        // Pushable
        PushStyleColor,
        PopStyleColor,
    };

    class WorkspaceDrawList {
      public:
        WorkspaceDrawList(ImDrawList* drawList);

        void AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments = 0, int zIndex = 0);
        void AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments = 0, int zIndex = 0);
        void AddCircleFilledColors(const ImVec2& center, float radius, std::vector<ImU32> colors, int num_segments = 0, int zIndex = 0);
        void AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness = 1.0f, int zIndex = 0);
        void AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0, float thickness = 1.0f, int zIndex = 0);
        void AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding = 0.0f, ImDrawFlags flags = 0, int zIndex = 0);
        void AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, int zIndex = 0);

        bool AddButton(const ImVec2& position, const std::string& label, int zIndex = 0);
        void AddCheckbox(const ImVec2& position, const std::string& label, bool* value, bool disabled, int zIndex = 0);
        void AddDragFloat(const ImVec2& position, const std::string& id, float* value, bool disabled, float width, int zIndex = 0);
        void AddImage(const ImVec2& position, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1),
                      const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0), int zIndex = 0);
        void AddText(const ImVec2& pos, ImU32 col, const char* text_begin, int zIndex = 0);
        void AddTextArea(const ImVec2& position, std::string_view label, bool multiline, std::string* text, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextCallback callback = 0,
                         void* userData = nullptr, int zIndex = 0);

        void PushStyleColor(ImGuiCol idx, ImU32 col, int zIndex = 0);
        void PushStyleColor(ImGuiCol idx, const ImVec4& col, int zIndex = 0);
        void PopStyleColor(int zIndex = 0);

        void Flush();

      private:
        void DrawBezierCubic(BezierCubic& cubic);
        void DrawCircleFilled(CircleFilled& circle);
        void DrawCircleFilledColors(CircleFilledColors& circle);
        void DrawLine(Line& line);
        void DrawRect(Rect& rect);
        void DrawRectFilled(RectFilled& rect);
        void DrawTriangleFilled(TriangleFilled& triangle);

        void DrawButton(Button& button);
        void DrawCheckbox(Checkbox& checkbox);
        void DrawDragFloat(DragFloat& f);
        void DrawImage(Image& image);
        void DrawText(Text& text);
        void DrawTextArea(TextArea& textArea);

        void PushStyleColor(StyleColor& styleColor);

      private:
        std::map<int, std::queue<InstructionType>>    m_DrawableInserts;

        std::map<int, std::queue<BezierCubic>>        m_BezierCubics;
        std::map<int, std::queue<CircleFilled>>       m_CirclesFilled;
        std::map<int, std::queue<CircleFilledColors>> m_CirclesFilledColors;
        std::map<int, std::queue<Line>>               m_Lines;
        std::map<int, std::queue<Rect>>               m_Rects;
        std::map<int, std::queue<RectFilled>>         m_RectsFilled;
        std::map<int, std::queue<TriangleFilled>>     m_TrianglesFilled;

        std::map<int, std::queue<Button>>             m_Buttons;
        std::map<int, std::queue<Checkbox>>           m_Checkboxes;
        std::map<int, std::queue<DragFloat>>          m_DragFloats;
        std::map<int, std::queue<Image>>              m_Images;
        std::map<int, std::queue<Text>>               m_Texts;
        std::map<int, std::queue<TextArea>>           m_TextAreas;

        std::map<int, std::queue<StyleColor>>         m_StyleColors;

        ImDrawList*                                   m_DrawList;
    };
}
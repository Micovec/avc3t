#include "WorkspaceDrawList.h"

#include <array>

#include "imgui.h"
#include "imgui_internal.h"
#include "../utils/ImGuiUtils.h"

namespace AVC3T {
    WorkspaceDrawList::WorkspaceDrawList(ImDrawList* drawList) :
        m_DrawableInserts(), m_BezierCubics(), m_CirclesFilled(), m_Lines(), m_Rects(), m_RectsFilled(), m_TrianglesFilled(), m_Buttons(), m_Checkboxes(), // Drawables
        m_DragFloats(), m_Texts(), m_StyleColors(),                                                                                                        // Pushables
        m_DrawList(drawList) {}

    void WorkspaceDrawList::AddBezierCubic(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thickness, int num_segments, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::BezierCubic);
        m_BezierCubics[zIndex].emplace(BezierCubic(p1, p2, p3, p4, col, thickness, num_segments));
    }

    void WorkspaceDrawList::AddCircleFilled(const ImVec2& center, float radius, ImU32 col, int num_segments, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::CircleFilled);
        m_CirclesFilled[zIndex].emplace(CircleFilled(center, radius, col, num_segments));
    }

    void WorkspaceDrawList::AddCircleFilledColors(const ImVec2& center, float radius, std::vector<ImU32> colors, int num_segments, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::CircleFilledColors);
        m_CirclesFilledColors[zIndex].emplace(CircleFilledColors(center, radius, colors, num_segments));
    }

    void WorkspaceDrawList::AddLine(const ImVec2& p1, const ImVec2& p2, ImU32 col, float thickness, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Line);
        m_Lines[zIndex].emplace(Line(p1, p2, col, thickness));
    }

    void WorkspaceDrawList::AddRect(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding, ImDrawFlags flags, float thickness, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Rect);
        m_Rects[zIndex].emplace(Rect(p_min, p_max, col, rounding, flags, thickness));
    }

    void WorkspaceDrawList::AddRectFilled(const ImVec2& p_min, const ImVec2& p_max, ImU32 col, float rounding, ImDrawFlags flags, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::RectFilled);
        m_RectsFilled[zIndex].emplace(RectFilled(p_min, p_max, col, rounding, flags));
    }

    void WorkspaceDrawList::AddTriangleFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, ImU32 col, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::TriangleFilled);
        m_TrianglesFilled[zIndex].emplace(TriangleFilled(p1, p2, p3, col));
    }

    //-----------------
    // INPUT
    //-----------------
    bool WorkspaceDrawList::AddButton(const ImVec2& position, const std::string& label, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Button);
        m_Buttons[zIndex].emplace(Button(position, label));

        const ImVec2      label_size = ImGui::CalcTextSize(label.c_str());

        const ImGuiStyle& style = ImGui::GetStyle();
        ImVec2            size  = ImVec2(label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        ImGui::SetCursorScreenPos(position);
        return ImGui::InvisibleButton(label.c_str(), size);
    }

    void WorkspaceDrawList::AddCheckbox(const ImVec2& position, const std::string& label, bool* value, bool disabled, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Checkbox);
        m_Checkboxes[zIndex].emplace(Checkbox(position, label, value, disabled));
    }

    void WorkspaceDrawList::AddDragFloat(const ImVec2& position, const std::string& id, float* value, bool disabled, float width, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::DragFloat);
        m_DragFloats[zIndex].emplace(DragFloat(position, id, value, disabled, width));
    }

    void WorkspaceDrawList::AddImage(const ImVec2& position, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col,
                                     const ImVec4& border_col, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Image);
        m_Images[zIndex].emplace(Image(position, user_texture_id, size, uv0, uv1, tint_col, border_col));
    }

    void WorkspaceDrawList::AddText(const ImVec2& pos, ImU32 col, const char* text_begin, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::Text);
        m_Texts[zIndex].emplace(Text(pos, col, text_begin));
    }

    void WorkspaceDrawList::AddTextArea(const ImVec2& position, std::string_view label, bool multiline, std::string* text, const ImVec2& size, ImGuiInputTextCallback callback,
                                        void* userData, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::TextArea);
        m_TextAreas[zIndex].emplace(TextArea(position, label, multiline, text, size, callback, userData));
    }

    //-----------------
    // STYLE
    //-----------------
    void WorkspaceDrawList::PushStyleColor(ImGuiCol idx, ImU32 col, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::PushStyleColor);
        m_StyleColors[zIndex].emplace(StyleColor(idx, col));
    }

    void WorkspaceDrawList::PushStyleColor(ImGuiCol idx, const ImVec4& col, int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::PushStyleColor);
        m_StyleColors[zIndex].emplace(StyleColor(idx, ImGui::ColorConvertFloat4ToU32(col)));
    }

    void WorkspaceDrawList::PopStyleColor(int zIndex) {
        m_DrawableInserts[zIndex].emplace(InstructionType::PopStyleColor);
    }

    void WorkspaceDrawList::Flush() {
        for (auto&& [index, inserts] : m_DrawableInserts) {
            while (!inserts.empty()) {
                InstructionType type = inserts.front();
                inserts.pop();

                switch (type) {
                    case InstructionType::BezierCubic:
                        DrawBezierCubic(m_BezierCubics[index].front());
                        m_BezierCubics[index].pop();
                        break;

                    case InstructionType::CircleFilled:
                        DrawCircleFilled(m_CirclesFilled[index].front());
                        m_CirclesFilled[index].pop();
                        break;

                    case InstructionType::CircleFilledColors:
                        DrawCircleFilledColors(m_CirclesFilledColors[index].front());
                        m_CirclesFilledColors[index].pop();
                        break;

                    case InstructionType::Line:
                        DrawLine(m_Lines[index].front());
                        m_Lines[index].pop();
                        break;

                    case InstructionType::Rect:
                        DrawRect(m_Rects[index].front());
                        m_Rects[index].pop();
                        break;

                    case InstructionType::RectFilled:
                        DrawRectFilled(m_RectsFilled[index].front());
                        m_RectsFilled[index].pop();
                        break;

                    case InstructionType::TriangleFilled:
                        DrawTriangleFilled(m_TrianglesFilled[index].front());
                        m_TrianglesFilled[index].pop();
                        break;

                    case InstructionType::Button:
                        DrawButton(m_Buttons[index].front());
                        m_Buttons[index].pop();
                        break;

                    case InstructionType::Checkbox:
                        DrawCheckbox(m_Checkboxes[index].front());
                        m_Checkboxes[index].pop();
                        break;

                    case InstructionType::DragFloat:
                        DrawDragFloat(m_DragFloats[index].front());
                        m_DragFloats[index].pop();
                        break;

                    case InstructionType::Image:
                        DrawImage(m_Images[index].front());
                        m_Images[index].pop();
                        break;

                    case InstructionType::Text:
                        DrawText(m_Texts[index].front());
                        m_Texts[index].pop();
                        break;

                    case InstructionType::TextArea:
                        DrawTextArea(m_TextAreas[index].front());
                        m_TextAreas[index].pop();
                        break;

                    case InstructionType::PushStyleColor:
                        PushStyleColor(m_StyleColors[index].front());
                        m_StyleColors[index].pop();
                        break;

                    case InstructionType::PopStyleColor: ImGui::PopStyleColor(); break;

                    default: break;
                }
            }
        }
    }

    void WorkspaceDrawList::DrawBezierCubic(BezierCubic& cubic) {
        m_DrawList->AddBezierCubic(cubic.P1, cubic.P2, cubic.P3, cubic.P4, cubic.Color, cubic.Thickness, cubic.NumSegments);
    }

    void WorkspaceDrawList::DrawCircleFilled(CircleFilled& circle) {
        m_DrawList->AddCircleFilled(circle.Center, circle.Radius, circle.Color, circle.NumSegments);
    }

    void WorkspaceDrawList::DrawCircleFilledColors(CircleFilledColors& circle) {
        float aCurrent = 0;
        float aShift   = (IM_PI * 2) / circle.Colors.size();

        for (std::size_t i = 0; i < circle.Colors.size(); ++i, aCurrent += aShift) {
            m_DrawList->PathArcTo(circle.Center, circle.Radius, aCurrent, aCurrent + aShift, circle.NumSegments - 1);
            m_DrawList->PathLineTo(circle.Center);
            m_DrawList->PathFillConvex(circle.Colors[i]);
        }
    }

    void WorkspaceDrawList::DrawLine(Line& line) {
        m_DrawList->AddLine(line.P1, line.P2, line.Color, line.Thickness);
    }

    void WorkspaceDrawList::DrawRect(Rect& rect) {
        m_DrawList->AddRect(rect.PMin, rect.PMax, rect.Color, rect.Rounding, rect.Flags, rect.Thickness);
    }

    void WorkspaceDrawList::DrawRectFilled(RectFilled& rect) {
        m_DrawList->AddRectFilled(rect.PMin, rect.PMax, rect.Color, rect.Rounding, rect.Flags);
    }

    void WorkspaceDrawList::DrawTriangleFilled(TriangleFilled& triangle) {
        m_DrawList->AddTriangleFilled(triangle.P1, triangle.P2, triangle.P3, triangle.Color);
    }

    void WorkspaceDrawList::DrawDragFloat(DragFloat& f) {
        ImGui::PushItemWidth(f.Width);
        ImGui::SetCursorScreenPos(f.Position);
        ImGuiDragFloat(f.Id, f.Value, f.Disabled);
        ImGui::PopItemWidth();
    }

    void WorkspaceDrawList::DrawButton(Button& button) {
        ImGui::SetCursorScreenPos(button.Position);
        ImGui::Button(button.Label.data());
    }

    void WorkspaceDrawList::DrawCheckbox(Checkbox& checkbox) {
        ImGui::SetCursorScreenPos(checkbox.Position);
        //ImGui::Checkbox(checkbox.Label.data(), checkbox.Value);
        ImGuiCheckbox(checkbox.Label, checkbox.Value, checkbox.Disabled);
    }

    void WorkspaceDrawList::DrawImage(Image& image) {
        ImGui::SetCursorScreenPos(image.Position);
        ImGui::Image(image.TextureId, image.Size, image.UV0, image.UV1, image.TintColor, image.BorderColor);
    }

    void WorkspaceDrawList::DrawText(Text& text) {
        m_DrawList->AddText(text.Position, text.Color, text.SText.data());
    }

    void WorkspaceDrawList::DrawTextArea(TextArea& textArea) {
        ImGui::SetCursorScreenPos(textArea.Position);

        if (textArea.Multiline) {
            ImGui::InputTextMultiline(textArea.Label.data(), textArea.Text->data(), textArea.Text->capacity(), textArea.Size,
                                      ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackAlways, textArea.Callback,
                                      textArea.UserData);
        } else {
            ImGui::PushItemWidth(textArea.Size.x);
            ImGui::InputText(textArea.Label.data(), textArea.Text->data(), textArea.Text->capacity(),
                             ImGuiInputTextFlags_CallbackResize | ImGuiInputTextFlags_CallbackEdit | ImGuiInputTextFlags_CallbackAlways, textArea.Callback, textArea.UserData);
            ImGui::PopItemWidth();
        }
    }

    void WorkspaceDrawList::PushStyleColor(StyleColor& styleColor) {
        ImGui::PushStyleColor(styleColor.Index, styleColor.Color);
    }
}
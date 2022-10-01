#pragma once

#include <string>

#include <imgui/imgui.h>

static inline void ImGuiBeginFakeDisabled() {
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.85f);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, IM_COL32(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, IM_COL32(0, 0, 0, 0));
}

static inline void ImGuiEndFakeDisabled() {
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

static inline void ImGuiBeginDisabled() {
    ImGui::BeginDisabled();
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.85f);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
}

static inline void ImGuiEndDisabled() {
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::EndDisabled();
}

static inline void ImGuiDragFloat(const std::string& id, float* value, bool disabled) {
    if (disabled)
        ImGuiBeginDisabled();
    // TODO make drag float step optional
    ImGui::SetItemAllowOverlap();
    ImGui::DragFloat(id.data(), value, 0.01f);

    if (disabled)
        ImGuiEndDisabled();
}

static inline void ImGuiCheckbox(const std::string& id, bool* value, bool disabled) {
    if (disabled) {
        ImU32 frameBackgroundColor = ImGui::GetColorU32(ImGuiCol_FrameBg);
        ImGui::BeginDisabled();
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, frameBackgroundColor);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, frameBackgroundColor);
    }

    ImGui::SetItemAllowOverlap();
    ImGui::Checkbox(id.data(), value);

    if (disabled) {
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::EndDisabled();
    }
}

// TODO move remaining functions to a seperate file
static inline float Sign(const ImVec2& a, const ImVec2& b, const ImVec2& c) {
    return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

static inline bool IsPositionInsideRectanle(const ImVec2& position, const ImVec2& min, const ImVec2& max) {
    return position.x >= min.x && position.y >= min.y && position.x <= max.x && position.y <= max.y;
}

static inline bool IsPositionInsideCircle(const ImVec2& position, const ImVec2& center, float radius) {
    float deltaX = position.x - center.x;
    float deltaY = position.y - center.y;

    return deltaX * deltaX + deltaY * deltaY < radius * radius;
}

static inline bool IsPositionInsideTriangle(const ImVec2& position, const ImVec2& posA, const ImVec2& posB, const ImVec2& posC) {
    float d1, d2, d3;
    bool  has_neg, has_pos;

    d1 = Sign(position, posA, posB);
    d2 = Sign(position, posB, posC);
    d3 = Sign(position, posC, posA);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

static inline ImVec2 GetRelativePosition(const ImVec2& absolutePosition, const ImVec2& origin) {
    return ImVec2(absolutePosition.x - origin.x, absolutePosition.y - origin.y);
}
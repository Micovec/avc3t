#pragma once

#include <imgui/imgui.h>

namespace AVC3T {
    struct WorkspaceNodeStyle {
        WorkspaceNodeStyle(const ImColor& barColor) : WorkspaceNodeStyle(barColor, IM_COL32(230, 230, 230, 255)) {}

        WorkspaceNodeStyle(const ImColor& barColor, const ImColor& titleTextColor) :
            BarBackgroundColor(barColor),
            BarBackgroundColorHovered(barColor.Value.x + HoveredAddition, barColor.Value.y + HoveredAddition, barColor.Value.z + HoveredAddition, barColor.Value.w),
            BarBackgroundColorSelected(barColor.Value.x + SelectedAddition, barColor.Value.y + SelectedAddition, barColor.Value.z + SelectedAddition, barColor.Value.w),
            TitleTextColor(titleTextColor) {}

        WorkspaceNodeStyle(const ImColor& barColor, const ImColor& titleTextColor, const ImColor& backgroundColor) :
            BarBackgroundColor(barColor), TitleTextColor(titleTextColor), BackgroundColor(backgroundColor) {}

        WorkspaceNodeStyle(const ImColor& barColor, const ImColor& titleTextColor, const ImColor& barColorHovered, const ImColor& barColorSelected) :
            BarBackgroundColor(barColor), TitleTextColor(titleTextColor), BackgroundColorHovered(barColorHovered), BackgroundColorSelected(barColorSelected) {}

        WorkspaceNodeStyle(const ImColor& barColor, const ImColor& barColorHovered, const ImColor& barColorSelected, const ImColor& backgroundColor,
                           const ImColor& backgroundColorHovered, const ImColor& backgroundColorSelected) :
            BarBackgroundColor(barColor), BarBackgroundColorHovered(barColorHovered), BarBackgroundColorSelected(barColorSelected), BackgroundColor(backgroundColor),
            BackgroundColorHovered(backgroundColorHovered), BackgroundColorSelected(backgroundColorSelected) {}

        static constexpr float LineHeight              = 20;
        static constexpr float InputWidth              = 65;
        static constexpr float PinPadding              = 12;
        static constexpr float InputDescriptionPadding = 5;

        static constexpr float HoveredAddition  = 20 / 255.f;
        static constexpr float SelectedAddition = 10 / 255.f;

        // TODO: rename from title to: bar / top bar
        const ImColor BarBackgroundColor;
        const ImColor BarBackgroundColorHovered;
        const ImColor BarBackgroundColorSelected;

        const ImColor TitleTextColor;

        const ImColor BackgroundColor         = IM_COL32(55, 55, 55, 255);
        const ImColor BackgroundColorHovered  = IM_COL32(55, 55, 55, 255);
        const ImColor BackgroundColorSelected = IM_COL32(55, 55, 55, 255);

        ImVec4        ContentMargin = ImVec4(0, 6, 0, 6);
        const ImVec4  TitleMargin   = ImVec4(4, 4, 4, 4);
    };
}
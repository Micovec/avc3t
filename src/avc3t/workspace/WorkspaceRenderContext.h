#pragma once

#include "WorkspaceDrawList.h"
#include <memory>

namespace AVC3T {
    class Workspace;

    struct WorkspaceRenderContext {
        WorkspaceRenderContext(ImDrawList* drawList, const ImVec2& topLeft, const ImVec2& bottomRight, const ImVec2& scrolling, const ImVec2& origin, const ImVec2& size) :
            DrawList(std::make_shared<WorkspaceDrawList>(drawList)), TopLeft(topLeft), BottomRight(bottomRight), Scrolling(scrolling), Origin(origin), Size(size) {}

        WorkspaceRenderContext(WorkspaceRenderContext& other, const ImVec2& shift) :
            DrawList(other.DrawList), TopLeft(other.TopLeft), BottomRight(other.BottomRight), Scrolling(other.Scrolling.x - shift.x, other.Scrolling.y - shift.y),
            Origin(other.TopLeft.x + other.Scrolling.x + shift.x, other.TopLeft.y + other.Scrolling.y + shift.y), Size(other.Size) {}

        std::shared_ptr<WorkspaceDrawList> DrawList;
        const ImVec2                       TopLeft;
        const ImVec2                       BottomRight;

        const ImVec2                       Scrolling;
        const ImVec2                       Origin;
        const ImVec2                       Size;
    };
}
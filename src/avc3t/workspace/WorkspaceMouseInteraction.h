#pragma once

#include <memory>
#include <vector>

#include <imgui/imgui.h>

#include "../ui/MouseButton.h"

namespace AVC3T {
    class WorkspaceElement;

    struct WorkspaceMouseInteraction {
        WorkspaceMouseInteraction(MouseButton mouseButton, const ImVec2& _mousePosition, bool handled) :
            mouseButton(mouseButton), mousePosition(_mousePosition), Handled(handled) {}

        WorkspaceMouseInteraction(const WorkspaceMouseInteraction& other, const ImVec2& newPosition) :
            mouseButton(other.mouseButton), mousePosition(newPosition), Handled(other.Handled) {}

        WorkspaceMouseInteraction(const WorkspaceMouseInteraction& other) : mouseButton(other.mouseButton), mousePosition(other.mousePosition), Handled(other.Handled) {}

        const MouseButton mouseButton;
        const ImVec2      mousePosition;
        const bool        Handled;
    };
} // namespace AVC3T
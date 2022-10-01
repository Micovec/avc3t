#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "WorkspaceMouseInteractionResult.h"
#include "../ui/MouseButton.h"
#include "node/WorkspaceNodeBinder.h"
#include "WorkspaceTime.h"

namespace AVC3T {
    class Workspace {
      public:
        Workspace() :
            m_Elements(), m_SelectedElements(), m_MouseInteractionResult(), m_CreatingLinkOutputPin(nullptr), m_LastMousePosUpdate(), m_LastMousePosSelecting(),
            m_IsAreaSelecting(false), m_Links(), m_Scrolling(), m_Time() {}

        void Render(ImDrawList* drawList, const ImVec2& topLeft, const ImVec2& bottomRight, const ImVec2& size);
        void Update(double ts);

        // User performed a click = mouse's position did not change between pressing to releasing
        // Returns bool if user clicked on ui control
        WorkspaceMouseInteractionResult MouseClicked(MouseButton mouseButton, const ImVec2& position);
        // Mouse button got pressed
        void MousePressed(MouseButton mouseButton, const ImVec2& position);
        // Mouse button is held down
        void                            MouseReleased(MouseButton mouseButton, const ImVec2& position);

        WorkspaceMouseInteractionResult MousePositionUpdate(const ImVec2& mousePos);
        void                            MouseDrag(MouseButton mouseButton, const ImVec2& delta);

        void                            ResetScrolling() {
            m_Scrolling = ImVec2(0, 0);
        }
        const ImVec2& GetScrolling() const {
            return m_Scrolling;
        }

        void                                                                         AddNode(const std::shared_ptr<WorkspaceNode> node);
        void                                                                         CreateLink(WorkspaceInputPin* inputPin, WorkspaceOutputPin* outputPin);
        void                                                                         DuplicateSelectedNodes();

        void                                                                         DeleteSelectedNodes();
        void                                                                         DeleteLink(WorkspaceLink* link);

        void                                                                         Clear();

        const std::map<std::size_t, std::vector<std::shared_ptr<WorkspaceElement>>>& GetElements() const {
            return m_Elements;
        }
        WorkspaceTime& GetTime() {
            return m_Time;
        }

      public:
        constexpr static ImVec2 s_DuplicationShift = ImVec2(20, 20);

      private:
        void RenderElements(WorkspaceRenderContext& context);
        void RenderGrid(WorkspaceRenderContext& context);
        void RenderDragLink(WorkspaceRenderContext& context);

        void AreaSelect(const ImVec2& min, const ImVec2& max);
        void AddSelectedNode(WorkspaceElement* element);
        void ClearSelectedElements(InteractedElementType exceptionType);

        bool WouldLinkCreateCircle(WorkspaceInputPin* inputPin, std::set<WorkspaceNode*> walkedNodes);

      private:
        std::map<std::size_t, std::vector<std::shared_ptr<WorkspaceElement>>> m_Elements;
        // TODO this is stupid, find a better way to store selected elements
        std::map<int, std::vector<WorkspaceElement*>> m_SelectedElements;
        WorkspaceMouseInteractionResult               m_MouseInteractionResult;
        WorkspaceOutputPin*                           m_CreatingLinkOutputPin;
        ImVec2                                        m_LastMousePosUpdate, m_LastMousePosSelecting;
        bool                                          m_IsAreaSelecting;

        std::vector<std::shared_ptr<WorkspaceLink>>   m_Links;

        ImVec2                                        m_Scrolling;
        WorkspaceTime                                 m_Time;

      private:
        constexpr static size_t s_NodeIndex    = 0;
        constexpr static size_t s_LinkIndex    = 2;
        constexpr static size_t s_ElementIndex = 3;
    };
}
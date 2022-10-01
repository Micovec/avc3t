#include "Workspace.h"
#include "../utils/ImGuiUtils.h"
#include "../ui/TextPopupModal.h"

namespace AVC3T {
    void Workspace::Render(ImDrawList* drawList, const ImVec2& topLeft, const ImVec2& bottomRight, const ImVec2& size) {
        const ImVec2           origin(topLeft.x + m_Scrolling.x, topLeft.y + m_Scrolling.y);

        WorkspaceRenderContext context(drawList, topLeft, bottomRight, m_Scrolling, origin, size);
        RenderGrid(context);

        RenderDragLink(context);
        RenderElements(context);

        if (m_IsAreaSelecting) {
            ImVec2 min = m_LastMousePosSelecting;
            min.x += context.Origin.x;
            min.y += context.Origin.y;

            ImVec2 max(m_LastMousePosUpdate.x, m_LastMousePosUpdate.y);
            max.x += context.Origin.x;
            max.y += context.Origin.y;

            context.DrawList->AddRectFilled(min, max, IM_COL32(17, 147, 247, 128));
            context.DrawList->AddRect(min, max, IM_COL32(17, 205, 247, 128));
        }

        context.DrawList->Flush();
    }

    void Workspace::Update(double ts) {
        m_Time.Update(ts);
        double time = m_Time.GetTime();

        // Delete all links that had been disabled last update call
        for (auto&& it = m_Links.begin(); it != m_Links.end();) {
            WorkspaceLink* link = it->get();
            if (link->OutputPin.Output.Disabled) {
                link->InputPin.Link = nullptr;
                link->OutputPin.Links.erase(std::find(link->OutputPin.Links.begin(), link->OutputPin.Links.end(), *it));

                m_Elements[s_LinkIndex].erase(std::find(m_Elements[s_LinkIndex].begin(), m_Elements[s_LinkIndex].end(), *it));
                it = m_Links.erase(it);
            } else {
                ++it;
            }
        }

        for (auto&& [_, elements] : m_Elements) {
            for (auto&& element : elements) {
                element->Evaluate(time);
            }
        }
    }

    void Workspace::RenderElements(WorkspaceRenderContext& context) {
        for (auto&& it = m_Elements.rbegin(); it != m_Elements.rend(); ++it) {
            auto& elements = it->second;

            for (auto&& node : elements) {
                node->Render(context);
            }
        }
    }

    void Workspace::RenderGrid(WorkspaceRenderContext& context) {
        const float GRID_STEP = 32.0f;
        for (float x = fmodf(m_Scrolling.x, GRID_STEP); x < context.Size.x; x += GRID_STEP)
            context.DrawList->AddLine(ImVec2(context.TopLeft.x + x, context.TopLeft.y), ImVec2(context.TopLeft.x + x, context.BottomRight.y), IM_COL32(150, 150, 150, 40), 1.5f);
        for (float y = fmodf(m_Scrolling.y, GRID_STEP); y < context.Size.y; y += GRID_STEP)
            context.DrawList->AddLine(ImVec2(context.TopLeft.x, context.TopLeft.y + y), ImVec2(context.BottomRight.x, context.TopLeft.y + y), IM_COL32(150, 150, 150, 40), 1.5f);
    }

    void Workspace::RenderDragLink(WorkspaceRenderContext& context) {
        if (m_CreatingLinkOutputPin != nullptr) {
            const ImVec2 pinPos(context.Origin.x + m_CreatingLinkOutputPin->Node->GetPosition().x + m_CreatingLinkOutputPin->GetPosition().x,
                                context.Origin.y + m_CreatingLinkOutputPin->Node->GetPosition().y + m_CreatingLinkOutputPin->GetPosition().y);
            const ImVec2 mousePos = ImGui::GetMousePos();

            const ImVec2 direction   = ImVec2(pinPos.x - mousePos.x, pinPos.y - mousePos.y);
            const float  bezierShift = powf(direction.x * direction.x + direction.y * direction.y, 0.42f);

            context.DrawList->AddBezierCubic(pinPos, ImVec2(pinPos.x + bezierShift, pinPos.y), ImVec2(mousePos.x - bezierShift, mousePos.y), mousePos, IM_COL32(255, 255, 255, 255),
                                             2, 20);
        }
    }

    void Workspace::AreaSelect(const ImVec2& min, const ImVec2& max) {
        ClearSelectedElements(InteractedElementType_None);

        for (auto&& element : m_Elements[s_NodeIndex]) {
            const ImVec2& topLeft = element->GetPosition();
            const ImVec2  bottomRight(topLeft.x + element->GetSize().x, topLeft.y + element->GetSize().y);

            if ((bottomRight.x >= min.x && bottomRight.y >= min.y) && (topLeft.x <= max.x && topLeft.y <= max.y)) {
                AddSelectedNode(static_cast<WorkspaceNode*>(element.get()));
            }
        }
    }

    void Workspace::AddSelectedNode(WorkspaceElement* element) {
        m_SelectedElements[InteractedElementType_NodeBar].push_back(element);
        element->AddFlags(WorkspaceInteractionFlags_Selected);
    }

    void Workspace::ClearSelectedElements(InteractedElementType exceptionType) {
        for (auto&& [type, elements] : m_SelectedElements) {
            if (exceptionType && (type & exceptionType))
                continue;

            for (auto& element : elements)
                element->RemoveFlags(WorkspaceInteractionFlags_Selected);

            elements.clear();
        }
    }

    WorkspaceMouseInteractionResult Workspace::MousePositionUpdate(const ImVec2& mousePos) {
        bool                            handled = false;
        WorkspaceMouseInteractionResult returnResult;

        for (auto&& it = m_Elements[s_NodeIndex].rbegin(); it != m_Elements[s_NodeIndex].rend(); ++it) {
            auto&& node             = *it;
            ImVec2 relativePosition = GetRelativePosition(mousePos, node->GetPosition());
            auto   result           = node->MousePositionUpdate(WorkspaceMouseInteraction(AVC3T::MouseButton::None, relativePosition, handled));

            if (!handled && result.Type != InteractedElementType_None) {
                m_MouseInteractionResult = result;
                handled                  = true;
                returnResult             = result;
            }
        }

        for (auto&& link : m_Elements[s_LinkIndex]) {
            auto result = link->MousePositionUpdate(WorkspaceMouseInteraction(AVC3T::MouseButton::None, mousePos, handled));

            if (!handled && result.Type != InteractedElementType_None) {
                m_MouseInteractionResult = result;
                handled                  = true;
                returnResult             = result;
            }
        }

        m_LastMousePosUpdate = mousePos;
        return returnResult;
    }

    WorkspaceMouseInteractionResult Workspace::MouseClicked(MouseButton mouseButton, const ImVec2& position) {
        for (auto&& [_, elements] : m_Elements) {
            for (auto&& it = elements.rbegin(); it != elements.rend(); ++it) {
                auto&& element = *it;

                ImVec2 relativePosition = GetRelativePosition(position, element->GetPosition());

                m_MouseInteractionResult = element->MouseClicked(WorkspaceMouseInteraction(mouseButton, relativePosition, false));

                if (m_MouseInteractionResult.Type != InteractedElementType_None)
                    return m_MouseInteractionResult;
            }
        }

        return WorkspaceMouseInteractionResult();
    }

    void Workspace::MousePressed(MouseButton mouseButton, const ImVec2& position) {
        if (mouseButton == MouseButton::Left) {
            m_CreatingLinkOutputPin = nullptr;
        }

        bool              handled         = false;
        WorkspaceElement* selectedElement = nullptr;
        m_MouseInteractionResult.Type     = InteractedElementType_None;

        for (auto&& [_, elements] : m_Elements) {
            for (auto&& it = elements.rbegin(); it != elements.rend(); ++it) {
                auto&& element = *it;

                ImVec2 relativePosition = GetRelativePosition(position, element->GetPosition());

                auto   result = element->MousePressed(WorkspaceMouseInteraction(mouseButton, relativePosition, handled));
                if (!handled && result.Type != InteractedElementType_None)
                    m_MouseInteractionResult = result;

                handled |= result.Type != InteractedElementType_None;
            }
        }

        InteractedElementType type = m_MouseInteractionResult.Type;
        ClearSelectedElements(type);

        if (type != InteractedElementType_None) {
            if (mouseButton == MouseButton::Left) {
                switch (type) {
                    case InteractedElementType_OutputPin: {
                        WorkspaceOutputPin* outputPin = std::get<WorkspaceOutputPin*>(m_MouseInteractionResult.Value);
                        if (!outputPin->Output.Disabled)
                            m_CreatingLinkOutputPin = outputPin;
                        break;
                    }

                    case InteractedElementType_NodeBar: selectedElement = std::get<WorkspaceNode*>(m_MouseInteractionResult.Value); break;

                    case InteractedElementType_Element: selectedElement = std::get<WorkspaceElement*>(m_MouseInteractionResult.Value); break;

                    default: break;
                }
            } else if (mouseButton == MouseButton::Right && type == InteractedElementType_NodeBar) {
                selectedElement = std::get<WorkspaceNode*>(m_MouseInteractionResult.Value);
            }

            if (selectedElement != nullptr) {
                auto it = std::find(m_SelectedElements[type].begin(), m_SelectedElements[type].end(), selectedElement);
                if (it == m_SelectedElements[type].end()) {
                    if (!ImGui::IsKeyDown(ImGuiKey_LeftShift))
                        ClearSelectedElements(InteractedElementType_None);
                    AddSelectedNode(selectedElement);
                }
            }
        }

        if (mouseButton == MouseButton::Left && type == InteractedElementType_None) {
            m_IsAreaSelecting       = true;
            m_LastMousePosSelecting = position;
        }
    }

    void Workspace::MouseReleased(MouseButton mouseButton, const ImVec2& position) {
        bool handled = false;
        if (m_IsAreaSelecting && mouseButton == MouseButton::Left) {
            ImVec2 min(std::min(m_LastMousePosSelecting.x, position.x), std::min(m_LastMousePosSelecting.y, position.y));
            ImVec2 max(std::max(m_LastMousePosSelecting.x, position.x), std::max(m_LastMousePosSelecting.y, position.y));

            AreaSelect(min, max);
        } else {
            m_MouseInteractionResult.Type = InteractedElementType_None;
            for (auto&& [zIndex, elements] : m_Elements) {
                for (auto&& it = elements.rbegin(); it != elements.rend(); ++it) {
                    auto&& element = *it;

                    ImVec2 relativePosition = GetRelativePosition(position, element->GetPosition());

                    auto   result = element->MouseReleased(WorkspaceMouseInteraction(mouseButton, relativePosition, handled));
                    if (!handled && result.Type != InteractedElementType_None)
                        m_MouseInteractionResult = result;

                    handled = result.Type != InteractedElementType_None;

                    if (m_CreatingLinkOutputPin != nullptr && m_MouseInteractionResult.Type == InteractedElementType_InputPin) {
                        WorkspaceInputPin* inputPin = std::get<WorkspaceInputPin*>(m_MouseInteractionResult.Value);

                        if (inputPin->Link == nullptr && inputPin->Input.Type & m_CreatingLinkOutputPin->Output.Type) {
                            CreateLink(inputPin, m_CreatingLinkOutputPin);
                        }

                        m_CreatingLinkOutputPin = nullptr;
                    }
                }
            }
        }

        if (mouseButton == MouseButton::Left) {
            m_CreatingLinkOutputPin = nullptr;
            m_IsAreaSelecting       = false;
        }
    }

    void Workspace::MouseDrag(MouseButton mouseButton, const ImVec2& delta) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);

        switch (mouseButton) {
            case MouseButton::Right:
                m_Scrolling.x += delta.x;
                m_Scrolling.y += delta.y;
                ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeAll);
                break;

            case MouseButton::Left: {
                for (auto&& [_, elements] : m_SelectedElements) {
                    for (auto&& element : elements) {
                        const ImVec2& position = element->GetPosition();
                        element->SetPosition(ImVec2(position.x + delta.x, position.y + delta.y));
                    }
                }

                break;
            }
            default: break;
        }
    }

    void Workspace::AddNode(const std::shared_ptr<WorkspaceNode> node) {
        m_Elements[s_NodeIndex].push_back(node);
    }

    void Workspace::CreateLink(WorkspaceInputPin* inputPin, WorkspaceOutputPin* outputPin) {
        std::set<WorkspaceNode*> walkedNodes;
        walkedNodes.insert(outputPin->Node);

        if (WouldLinkCreateCircle(inputPin, walkedNodes)) {
            TextPopupModal::Open("Invalid operation", "Cannot create link because it would create a loop.");
            return;
        }

        m_Links.emplace_back(std::make_shared<WorkspaceLink>(*inputPin, *outputPin));
        m_Elements[s_LinkIndex].push_back(m_Links.back());

        inputPin->Link = m_Links.back();
        outputPin->Links.push_back(inputPin->Link);
    }

    bool Workspace::WouldLinkCreateCircle(WorkspaceInputPin* inputPin, std::set<WorkspaceNode*> walkedNodes) {
        if (walkedNodes.contains(inputPin->Node))
            return true;

        for (auto& pin : inputPin->Node->GetOutputPins()) {
            for (auto& link : pin->Links) {
                if (WouldLinkCreateCircle(&link->InputPin, walkedNodes))
                    return true;
            }
        }

        return false;
    }

    void Workspace::DuplicateSelectedNodes() {
        std::vector<WorkspaceElement*>           selectedNodes = m_SelectedElements[InteractedElementType_NodeBar];
        std::map<WorkspaceNode*, WorkspaceNode*> nodePairs;

        ClearSelectedElements(InteractedElementType_None);

        // Duplicate nodes
        for (auto& node : selectedNodes) {
            WorkspaceNode*                 nodePtr        = static_cast<WorkspaceNode*>(node);
            std::shared_ptr<WorkspaceNode> duplicatedNode = nodePtr->Copy();
            nodePairs.insert({nodePtr, duplicatedNode.get()});

            ImVec2 position = node->GetPosition();
            position.x += s_DuplicationShift.x;
            position.y += s_DuplicationShift.y;
            duplicatedNode->SetPosition(position);

            m_Elements[s_NodeIndex].push_back(duplicatedNode);

            AddSelectedNode(duplicatedNode.get());
        }

        // Duplicate links
        // This is not the best algorithm to duplicate links. Time complexity is something like O(n^(m^(o^p)))
        // n = number of duplicated nodes, m = number of outputs per node, o = number of links per output, p = number of connected node's inputs
        // but since those values are realitively small and not even in tens, there's no need to worry to hit some performance issues
        for (auto& [originalNode, duplicatedNode] : nodePairs) {
            auto& outputPins = originalNode->GetOutputPins();
            for (std::size_t outputPinIndex = 0; outputPinIndex < outputPins.size(); ++outputPinIndex) {
                for (auto& link : outputPins[outputPinIndex]->Links) {
                    WorkspaceNode* otherOriginalNode = link->InputPin.Node;

                    if (nodePairs.find(otherOriginalNode) == nodePairs.end())
                        continue;

                    std::size_t inputPinIndex = -1;
                    {
                        auto& inputPins = otherOriginalNode->GetInputPins();
                        for (std::size_t index = 0; index < inputPins.size(); ++index) {
                            if (inputPins[index]->Link == link) {
                                inputPinIndex = index;
                                break;
                            }
                        }
                    }

                    WorkspaceNode* otherDuplicatedNode = nodePairs[link->InputPin.Node];

                    CreateLink(otherDuplicatedNode->GetInputPins()[inputPinIndex].get(), duplicatedNode->GetOutputPins()[outputPinIndex].get());
                }
            }
        }
    }

    void Workspace::DeleteSelectedNodes() {
        auto& elements = m_Elements[s_NodeIndex];

        for (auto& _node : m_SelectedElements[InteractedElementType_NodeBar]) {
            for (auto&& it = elements.begin(); it != elements.end(); ++it) {
                if (it->get() == _node) {
                    WorkspaceNode* node = static_cast<WorkspaceNode*>(_node);
                    // Delete input links
                    for (auto&& input : node->GetInputPins()) {
                        if (input->Link == nullptr)
                            continue;

                        auto&& outputLinks = input->Link->OutputPin.Links;
                        for (auto&& it = outputLinks.begin(); it != outputLinks.end(); ++it) {
                            if (*it == input->Link) {
                                outputLinks.erase(it);
                                break;
                            }
                        }

                        m_Links.erase(std::find(m_Links.begin(), m_Links.end(), input->Link));
                        m_Elements[s_LinkIndex].erase(std::find(m_Elements[s_LinkIndex].begin(), m_Elements[s_LinkIndex].end(), input->Link));
                    }

                    // Delete output links
                    for (auto&& output : node->GetOutputPins()) {
                        for (auto&& it = output->Links.begin(); it != output->Links.end(); ++it) {
                            (*it)->InputPin.Link = nullptr;
                            m_Links.erase(std::find(m_Links.begin(), m_Links.end(), *it));
                            m_Elements[s_LinkIndex].erase(std::find(m_Elements[s_LinkIndex].begin(), m_Elements[s_LinkIndex].end(), *it));
                        }
                    }

                    elements.erase(it);
                    break;
                }
            }
        }

        m_SelectedElements[InteractedElementType_NodeBar].clear();
    }

    void Workspace::DeleteLink(WorkspaceLink* link) {
        for (auto&& it = m_Links.begin(); it != m_Links.end(); ++it) {
            if (it->get() == link) {
                link->InputPin.Link = nullptr;

                for (auto&& it = link->OutputPin.Links.begin(); it != link->OutputPin.Links.end(); ++it) {
                    if (it->get() == link) {
                        link->OutputPin.Links.erase(it);
                        break;
                    }
                }

                m_Links.erase(it);
                break;
            }
        }

        auto& elements = m_Elements[s_LinkIndex];
        for (auto&& it = elements.begin(); it != elements.end(); ++it) {
            if (it->get() == link) {
                elements.erase(it);
                break;
            }
        }
    }

    void Workspace::Clear() {
        m_CreatingLinkOutputPin       = nullptr;
        m_MouseInteractionResult.Type = InteractedElementType_None;

        for (auto&& elements : m_SelectedElements)
            elements.second.clear();

        m_Links.clear();
        m_Elements.clear();
    }
}
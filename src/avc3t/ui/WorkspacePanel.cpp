#include "WorkspacePanel.h"

#include <math.h>

#include "../library/LibraryRecordNames.h"

#include "../workspace/node/WorkspaceNodeBinder.h"
#include "../workspace/WorkspaceRenderContext.h"

#include "../utils/ImGuiUtils.h"
#include "imgui.h"

namespace AVC3T {
    WorkspacePanel::WorkspacePanel(const std::shared_ptr<ScenePanel>& scenePanel) : m_ScenePanel(scenePanel), m_EditTextPopup(), m_Workspace(), m_MouseInteractionResult() {}

    void WorkspacePanel::Render() {
        ImGui::Begin("Workspace", nullptr, ImGuiWindowFlags_NoScrollbar);

        // Preventing vertical scroll by shifting canvas downwards
        float yScroll = ImGui::GetScrollY();
        ImGui::SetScrollY(0);

        ImVec2 canvasTopLeft = ImGui::GetCursorScreenPos();    // ImDrawList API uses screen coordinates!
        ImVec2 canvasSize    = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
        if (canvasSize.x < 50.0f)
            canvasSize.x = 50.0f;
        if (canvasSize.y < 50.0f)
            canvasSize.y = 50.0f;

        canvasTopLeft.y += yScroll;
        ImVec2      canvasBottomRight = ImVec2(canvasTopLeft.x + canvasSize.x, canvasTopLeft.y + canvasSize.y);

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        ImGui::SetCursorScreenPos(canvasTopLeft);
        bool disableInput = HandleCursorWorkspaceInteraction();

        // Fill background with 50, 50, 50, 255
        drawList->AddRectFilled(canvasTopLeft, canvasBottomRight, IM_COL32(36, 35, 43, 255));

        // Clip rect
        drawList->PushClipRect(canvasTopLeft, canvasBottomRight, true);

        m_EditTextPopup.Render();

        if (disableInput) {
            ImU32 alpha = ImGui::ColorConvertFloat4ToU32(ImGui::GetStyleColorVec4(ImGuiStyleVar_Alpha));

            ImGui::BeginDisabled();
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha / alpha);
        }

        m_Workspace.Render(drawList, canvasTopLeft, canvasBottomRight, canvasSize);

        if (disableInput) {
            ImGui::PopStyleVar();
            ImGui::EndDisabled();
        }

        drawList->PopClipRect();

        // Render border
        drawList->AddRect(canvasTopLeft, canvasBottomRight, IM_COL32(255, 255, 255, 255));

        ImGui::End();
    }

    void WorkspacePanel::Update(double ts) {
        m_Workspace.Update(ts);
    }

    bool WorkspacePanel::HandleCursorWorkspaceInteraction() {
        if (!IsMouseInsideWorkspace() || m_EditTextPopup.IsOpen()) {
            m_IsContextMenuShown = false;
            return false;
        }

        ImGuiIO&      io = ImGui::GetIO();

        ImVec2        mousePos = ImGui::GetMousePos();

        const ImVec2& scrolling     = m_Workspace.GetScrolling();
        ImVec2        canvasTopLeft = ImGui::GetCursorScreenPos();
        mousePos.x -= scrolling.x + canvasTopLeft.x;
        mousePos.y -= scrolling.y + canvasTopLeft.y;

        WorkspaceMouseInteractionResult updateResult = m_Workspace.MousePositionUpdate(mousePos);

        bool                            anyItemHovered = (updateResult.Type == InteractedElementType_None || m_IsContextMenuShown) && ImGui::IsAnyItemHovered();

        if (m_IsContextMenuShown)
            ShowContextMenu(mousePos);

        for (int i = 0; i < 2; ++i) {
            ImGuiMouseButton imMouseButton = static_cast<ImGuiMouseButton>(i);
            MouseButton      mouseButton   = static_cast<MouseButton>(i);

            if (ImGui::IsMouseDragging(imMouseButton) && !anyItemHovered)
                m_Workspace.MouseDrag(mouseButton, io.MouseDelta);

            if (ImGui::IsMouseClicked(imMouseButton)) {
                if (!anyItemHovered)
                    m_Workspace.MousePressed(mouseButton, mousePos);

                if (!ImGui::IsAnyItemHovered()) {
                    m_IsContextMenuShown = false;
                }
            }

            if (ImGui::IsMouseReleased(imMouseButton)) {
                m_Workspace.MouseReleased(mouseButton, mousePos);

                if (!anyItemHovered)
                    m_MouseInteractionResult = m_Workspace.MouseClicked(mouseButton, mousePos);

                if (mouseButton == MouseButton::Right) {
                    m_IsContextMenuShown = true;
                }
            }
        }

        return updateResult.Type != InteractedElementType_Input;
    }

    void WorkspacePanel::ShowContextMenu(const ImVec2& mousePos) {
        switch (m_MouseInteractionResult.Type) {
            case InteractedElementType_None: ShowWorkspaceContextMenu(mousePos); break;

            case InteractedElementType_NodeBar: ShowNodeContextMenu(mousePos, std::get<WorkspaceNode*>(m_MouseInteractionResult.Value), m_MouseInteractionResult.Options); break;

            case InteractedElementType_InputPin: ShowInputPinContextMenu(mousePos, std::get<WorkspaceInputPin*>(m_MouseInteractionResult.Value)); break;

            case InteractedElementType_OutputPin: ShowOutputPinContextMenu(mousePos, std::get<WorkspaceOutputPin*>(m_MouseInteractionResult.Value)); break;

            case InteractedElementType_Link: ShowLinkContextMenu(mousePos, std::get<WorkspaceLink*>(m_MouseInteractionResult.Value)); break;

            case InteractedElementType_NodeBody:
            default: break;
        }
    }

    void WorkspacePanel::ShowWorkspaceContextMenu(const ImVec2& mousePos) {
        ImGui::OpenPopup("workspacePopupContextMenu");

        if (ImGui::BeginPopup("workspacePopupContextMenu")) {
            std::shared_ptr<WorkspaceNode> newNode = nullptr;
            if (ImGui::BeginMenu("Value")) {
                if (ImGui::Selectable("Float"))
                    newNode = WorkspaceNodeBinder::NewFloatValue();

                if (ImGui::Selectable("Vec3"))
                    newNode = WorkspaceNodeBinder::NewVec3Value();

                if (ImGui::Selectable("Vec4"))
                    newNode = WorkspaceNodeBinder::NewVec4Value();

                if (ImGui::Selectable("Mat4"))
                    newNode = WorkspaceNodeBinder::NewMat4Value();

                if (ImGui::Selectable("Quat"))
                    newNode = WorkspaceNodeBinder::NewQuatValue();

                ImGui::Separator();

                if (ImGui::BeginMenu("Transformation")) {
                    if (ImGui::Selectable("Translation"))
                        newNode = WorkspaceNodeBinder::NewTransfTranslValue();

                    if (ImGui::Selectable("Scale"))
                        newNode = WorkspaceNodeBinder::NewTransfScaleValue();

                    if (ImGui::Selectable("Rotation"))
                        newNode = WorkspaceNodeBinder::NewTransfRotationValue();

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Operator")) {
                if (ImGui::BeginMenu("Float")) {
                    if (ImGui::Selectable("Float + Float"))
                        newNode = WorkspaceNodeBinder::NewFloatAdd();

                    if (ImGui::Selectable("Float - Float"))
                        newNode = WorkspaceNodeBinder::NewFloatSubstract();

                    if (ImGui::Selectable("Float * Float"))
                        newNode = WorkspaceNodeBinder::NewFloatMultiply();

                    if (ImGui::Selectable("Float / Float"))
                        newNode = WorkspaceNodeBinder::NewFloatDivide();

                    if (ImGui::Selectable("Float ^ Float"))
                        newNode = WorkspaceNodeBinder::NewFloatPower();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec3")) {
                    if (ImGui::Selectable("Vec3 + Vec3"))
                        newNode = WorkspaceNodeBinder::NewVec3Add();

                    if (ImGui::Selectable("Vec3 - Vec3"))
                        newNode = WorkspaceNodeBinder::NewVec3Substract();

                    if (ImGui::Selectable("Vec3 * Vec3"))
                        newNode = WorkspaceNodeBinder::NewVec3Multiply();

                    if (ImGui::Selectable("Vec3 . Vec3"))
                        newNode = WorkspaceNodeBinder::NewVec3Dot();

                    if (ImGui::Selectable("Float * Vec3"))
                        newNode = WorkspaceNodeBinder::NewFloatMultVec3();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec4")) {
                    if (ImGui::Selectable("Vec4 + Vec4"))
                        newNode = WorkspaceNodeBinder::NewVec4Add();

                    if (ImGui::Selectable("Vec4 - Vec4"))
                        newNode = WorkspaceNodeBinder::NewVec4Substract();

                    if (ImGui::Selectable("Vec4 * Vec4"))
                        newNode = WorkspaceNodeBinder::NewVec4Multiply();

                    if (ImGui::Selectable("Vec4 . Vec4"))
                        newNode = WorkspaceNodeBinder::NewVec4Dot();

                    if (ImGui::Selectable("Float * Vec4"))
                        newNode = WorkspaceNodeBinder::NewFloatMultVec4();

                    if (ImGui::Selectable("Mat4 * Vec4"))
                        newNode = WorkspaceNodeBinder::NewMat4MultVec4();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Mat4")) {
                    if (ImGui::Selectable("Mat4 + Mat4"))
                        newNode = WorkspaceNodeBinder::NewMat4Add();

                    if (ImGui::Selectable("Mat4 - Mat4"))
                        newNode = WorkspaceNodeBinder::NewMat4Add();

                    if (ImGui::Selectable("Mat4 * Mat4"))
                        newNode = WorkspaceNodeBinder::NewMat4Mult();

                    if (ImGui::Selectable("Float * Mat4"))
                        newNode = WorkspaceNodeBinder::NewFloatMultMat4();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Quat")) {
                    if (ImGui::Selectable("Quat * Quat"))
                        newNode = WorkspaceNodeBinder::NewQuatMult();

                    if (ImGui::Selectable("Float * Quat"))
                        newNode = WorkspaceNodeBinder::NewFloatMultQuat();

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Transformation")) {
                if (ImGui::Selectable("Translation"))
                    newNode = WorkspaceNodeBinder::NewTransfTransl();

                if (ImGui::Selectable("Scale"))
                    newNode = WorkspaceNodeBinder::NewTransfScale();

                if (ImGui::Selectable("Rotation euler angle X"))
                    newNode = WorkspaceNodeBinder::NewTransfRotationX();

                if (ImGui::Selectable("Rotation euler angle Y"))
                    newNode = WorkspaceNodeBinder::NewTransfRotationY();

                if (ImGui::Selectable("Rotation euler angle Z"))
                    newNode = WorkspaceNodeBinder::NewTransfRotationZ();

                if (ImGui::Selectable("Rotation - vector + angle"))
                    newNode = WorkspaceNodeBinder::NewTransfRotationVector();

                if (ImGui::Selectable("Look at"))
                    newNode = WorkspaceNodeBinder::NewTransfLookAt();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Function")) {
                if (ImGui::BeginMenu("Float")) {
                    if (ImGui::Selectable("Sin"))
                        newNode = WorkspaceNodeBinder::NewSin();

                    if (ImGui::Selectable("Cos"))
                        newNode = WorkspaceNodeBinder::NewCos();

                    if (ImGui::Selectable("Asin"))
                        newNode = WorkspaceNodeBinder::NewAsin();

                    if (ImGui::Selectable("Acos"))
                        newNode = WorkspaceNodeBinder::NewAcos();

                    if (ImGui::Selectable("Abs"))
                        newNode = WorkspaceNodeBinder::NewAbs();

                    if (ImGui::Selectable("Ceil"))
                        newNode = WorkspaceNodeBinder::NewCeil();

                    if (ImGui::Selectable("Floor"))
                        newNode = WorkspaceNodeBinder::NewFloor();

                    if (ImGui::Selectable("Clamp"))
                        newNode = WorkspaceNodeBinder::NewClamp();

                    if (ImGui::Selectable("Mod"))
                        newNode = WorkspaceNodeBinder::NewMod();

                    if (ImGui::Selectable("Sign"))
                        newNode = WorkspaceNodeBinder::NewSign();

                    if (ImGui::Selectable("Mix"))
                        newNode = WorkspaceNodeBinder::NewFloatMix();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec3")) {
                    if (ImGui::Selectable("Normalize"))
                        newNode = WorkspaceNodeBinder::NewVec3Normalize();

                    if (ImGui::Selectable("Length"))
                        newNode = WorkspaceNodeBinder::NewVec3Length();

                    if (ImGui::Selectable("Mix"))
                        newNode = WorkspaceNodeBinder::NewVec3Mix();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec4")) {
                    if (ImGui::Selectable("Normalize"))
                        newNode = WorkspaceNodeBinder::NewVec4Normalize();

                    if (ImGui::Selectable("Mix"))
                        newNode = WorkspaceNodeBinder::NewVec4Mix();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Mat4")) {
                    if (ImGui::Selectable("Transpose"))
                        newNode = WorkspaceNodeBinder::NewMat4Tranpose();

                    if (ImGui::Selectable("Inverse"))
                        newNode = WorkspaceNodeBinder::NewMat4Inverse();

                    if (ImGui::Selectable("Determinant"))
                        newNode = WorkspaceNodeBinder::NewMat4Determinant();

                    if (ImGui::Selectable("Decompose"))
                        newNode = WorkspaceNodeBinder::NewMat4Decompose();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Quat")) {
                    if (ImGui::Selectable("Conjugate"))
                        newNode = WorkspaceNodeBinder::NewQuatConjugate();

                    if (ImGui::Selectable("Inverse"))
                        newNode = WorkspaceNodeBinder::NewQuatInverse();

                    if (ImGui::Selectable("Normalize"))
                        newNode = WorkspaceNodeBinder::NewQuatNormalize();

                    if (ImGui::Selectable("Length"))
                        newNode = WorkspaceNodeBinder::NewQuatLength();

                    if (ImGui::Selectable("Lerp"))
                        newNode = WorkspaceNodeBinder::NewQuatLerp();

                    if (ImGui::Selectable("Slerp"))
                        newNode = WorkspaceNodeBinder::NewQuatSlerp();

                    if (ImGui::Selectable("Quat * Vec3 * Quat*"))
                        newNode = WorkspaceNodeBinder::NewQuatVec3Quat();

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Conversion")) {
                if (ImGui::BeginMenu("Float")) {
                    if (ImGui::Selectable("3x Float -> Vec3"))
                        newNode = WorkspaceNodeBinder::NewConvFloatToVec3();

                    if (ImGui::Selectable("4x Float -> Vec4"))
                        newNode = WorkspaceNodeBinder::NewConvFloatToVec4();

                    if (ImGui::Selectable("16x Float -> Mat4"))
                        newNode = WorkspaceNodeBinder::NewConvFloatToMat4();

                    if (ImGui::Selectable("3x Float -> Quat"))
                        newNode = WorkspaceNodeBinder::NewConvFloatToQuat();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec3")) {
                    if (ImGui::Selectable("Vec3 -> 3x Float"))
                        newNode = WorkspaceNodeBinder::NewConvVec3ToFloat();

                    if (ImGui::Selectable("Vec3 + Float -> Vec4"))
                        newNode = WorkspaceNodeBinder::NewConvVec3FloatToVec3();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Vec4")) {
                    if (ImGui::Selectable("Vec4 -> 4x Float"))
                        newNode = WorkspaceNodeBinder::NewConvVec4ToFloat();

                    if (ImGui::Selectable("Vec4 -> Vec3 + Float"))
                        newNode = WorkspaceNodeBinder::NewConvVec4ToVec3Float();

                    if (ImGui::Selectable("4x Vec4 -> Mat4"))
                        newNode = WorkspaceNodeBinder::NewConvVec4ToMat4();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Mat4")) {
                    if (ImGui::Selectable("Mat4 -> 16x Float"))
                        newNode = WorkspaceNodeBinder::NewConvMat4ToFloat();

                    if (ImGui::Selectable("Mat4 -> 4x Vec4"))
                        newNode = WorkspaceNodeBinder::NewConvMat4ToVec4();

                    if (ImGui::Selectable("Mat4 -> Quat"))
                        newNode = WorkspaceNodeBinder::NewConvMat4ToQuat();

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Quat")) {
                    if (ImGui::Selectable("Quat -> 4x Float"))
                        newNode = WorkspaceNodeBinder::NewConvQuatToFloat();

                    if (ImGui::Selectable("Quat -> Mat4"))
                        newNode = WorkspaceNodeBinder::NewConvQuatToMat4();

                    ImGui::Separator();

                    if (ImGui::Selectable("Quat -> Angle + Axis"))
                        newNode = WorkspaceNodeBinder::NewConvQuatToAngleAxis();

                    if (ImGui::Selectable("Quat -> Euler"))
                        newNode = WorkspaceNodeBinder::NewConvQuatToEuler();

                    if (ImGui::Selectable("Angle + Axis -> Quat"))
                        newNode = WorkspaceNodeBinder::NewConvAngleAxisToQuat();

                    if (ImGui::Selectable("Euler -> Quat"))
                        newNode = WorkspaceNodeBinder::NewConvEulerToQuat();

                    if (ImGui::Selectable("Vec3 + Vec3 -> Quat"))
                        newNode = WorkspaceNodeBinder::NewConvVec3Vec3ToQuat();

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Projection")) {
                if (ImGui::Selectable("Orthographic"))
                    newNode = WorkspaceNodeBinder::NewProjOrtho();

                if (ImGui::Selectable("Perspective"))
                    newNode = WorkspaceNodeBinder::NewProjPerspective();

                if (ImGui::Selectable("Frustum"))
                    newNode = WorkspaceNodeBinder::NewProjFrustum();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Logical")) {
                if (ImGui::Selectable("Value"))
                    newNode = WorkspaceNodeBinder::NewBoolValue();

                ImGui::Separator();

                if (ImGui::Selectable("And"))
                    newNode = WorkspaceNodeBinder::NewBoolAnd();

                if (ImGui::Selectable("Or"))
                    newNode = WorkspaceNodeBinder::NewBoolOr();

                if (ImGui::Selectable("Xor"))
                    newNode = WorkspaceNodeBinder::NewBoolXor();

                if (ImGui::Selectable("Not"))
                    newNode = WorkspaceNodeBinder::NewBoolNot();

                ImGui::Separator();

                if (ImGui::Selectable("Equal"))
                    newNode = WorkspaceNodeBinder::NewCmpEqual();

                if (ImGui::Selectable("Not equal"))
                    newNode = WorkspaceNodeBinder::NewCmpNotEqual();

                if (ImGui::Selectable("Smaller"))
                    newNode = WorkspaceNodeBinder::NewCmpSmaller();

                if (ImGui::Selectable("Smaller equal"))
                    newNode = WorkspaceNodeBinder::NewCmpSmallerEqual();

                ImGui::Separator();

                if (ImGui::Selectable("Pick"))
                    newNode = WorkspaceNodeBinder::NewPick();

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Object")) {
                if (ImGui::Selectable(SCENE_OBJECT_CONE_NAME))
                    newNode = WorkspaceNodeBinder::NewSceneObject(m_ScenePanel->GetScene(), SCENE_OBJECT_CONE_NAME);

                if (ImGui::Selectable(SCENE_OBJECT_CUBE_NAME))
                    newNode = WorkspaceNodeBinder::NewSceneObject(m_ScenePanel->GetScene(), SCENE_OBJECT_CUBE_NAME);

                if (ImGui::Selectable(SCENE_OBJECT_CYLINDER_NAME))
                    newNode = WorkspaceNodeBinder::NewSceneObject(m_ScenePanel->GetScene(), SCENE_OBJECT_CYLINDER_NAME);

                if (ImGui::Selectable(SCENE_OBJECT_SPHERE_NAME))
                    newNode = WorkspaceNodeBinder::NewSceneObject(m_ScenePanel->GetScene(), SCENE_OBJECT_SPHERE_NAME);

                if (ImGui::Selectable(SCENE_OBJECT_VECTOR_NAME))
                    newNode = WorkspaceNodeBinder::NewSceneObject(m_ScenePanel->GetScene(), SCENE_OBJECT_VECTOR_NAME);

                ImGui::Separator();

                if (ImGui::Selectable("External"))
                    newNode = WorkspaceNodeBinder::NewExternalObject(m_ScenePanel->GetScene());

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Miscellaneous")) {
                if (ImGui::Selectable("Camera"))
                    newNode = WorkspaceNodeBinder::NewCamera(m_ScenePanel->GetScene());

                if (ImGui::Selectable("Text area"))
                    newNode = WorkspaceNodeBinder::NewTextArea();

                if (ImGui::Selectable("Time"))
                    newNode = WorkspaceNodeBinder::NewTime();

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::Selectable("Reset view")) {
                m_Workspace.ResetScrolling();
                m_IsContextMenuShown = false;
            }

            if (newNode != nullptr) {
                newNode->SetPosition(mousePos);
                m_Workspace.AddNode(newNode);
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    void WorkspacePanel::ShowNodeContextMenu(const ImVec2& mousePos, WorkspaceNode* node, std::vector<WorkspaceMouseInteractionOption>& additionalOptions) {
        ImGui::OpenPopup("nodePopupContextMenu");

        if (ImGui::BeginPopup("nodePopupContextMenu")) {
            if (ImGui::Selectable("Duplicate")) {
                m_Workspace.DuplicateSelectedNodes();
                m_IsContextMenuShown = false;
            }

            if (ImGui::Selectable("Edit description")) {
                m_EditTextPopup.Open("Edit description", node->GetTitle());
                m_IsContextMenuShown = false;
            }

            if (additionalOptions.size() > 0) {
                ImGui::Separator();

                std::function<void(std::vector<WorkspaceMouseInteractionOption>&)> recursiveMenuCreator = [&](std::vector<WorkspaceMouseInteractionOption>& options) {
                    for (auto&& it = options.begin(); it != options.end(); ++it) {
                        if (it->Suboptions.size() == 0) {
                            bool enabled = it->Enabled == nullptr ? true : *it->Enabled;
                            if (!enabled)
                                ImGui::BeginDisabled();

                            if (ImGui::Selectable(it->Label.data())) {
                                auto demand = it->Callback(it->Data);

                                switch (demand.DemandType) {
                                    case InteractionOptionCallbackDemandType_AddNode: m_Workspace.AddNode(std::get<std::shared_ptr<WorkspaceNode>>(demand.Value)); break;

                                    default: break;
                                }

                                m_IsContextMenuShown = false;
                            }

                            if (!enabled)
                                ImGui::EndDisabled();
                        } else {
                            if (ImGui::BeginMenu(it->Label.data())) {
                                recursiveMenuCreator(it->Suboptions);

                                ImGui::EndMenu();
                            }
                        }
                    }
                };

                recursiveMenuCreator(additionalOptions);
            }

            ImGui::Separator();

            if (ImGui::Selectable("Delete")) {
                m_Workspace.DeleteSelectedNodes();
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    void WorkspacePanel::ShowInputPinContextMenu(const ImVec2& mousePos, WorkspaceInputPin* pin) {
        ImGui::OpenPopup("inputPinPopupContextMenu");

        if (ImGui::BeginPopup("inputPinPopupContextMenu")) {
            bool isLinkNull = pin->Link == nullptr;
            if (isLinkNull)
                ImGuiBeginFakeDisabled();

            if (ImGui::Selectable("Disconnect")) {
                m_Workspace.DeleteLink(pin->Link.get());
                m_IsContextMenuShown = false;
            }

            if (isLinkNull)
                ImGuiEndFakeDisabled();

            if (ImGui::Selectable("Edit description")) {
                m_EditTextPopup.Open("Edit description", pin->Description);
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    void WorkspacePanel::ShowOutputPinContextMenu(const ImVec2& mousePos, WorkspaceOutputPin* pin) {
        ImGui::OpenPopup("outputPinPopupContextMenu");

        if (ImGui::BeginPopup("outputPinPopupContextMenu")) {
            if (pin->Links.size() == 0) {
                ImGuiBeginFakeDisabled();

                if (ImGui::Selectable("Disconnect"))
                    m_IsContextMenuShown = false;

                ImGuiEndFakeDisabled();
            } else if (ImGui::BeginMenu("Disconnect")) {
                WorkspaceLink* linkToDisconnect = nullptr;
                int            i                = 0;
                for (auto&& link = pin->Links.begin(); link != pin->Links.end(); ++link) {
                    std::string id = (*link)->InputPin.Node->GetTitle() + "##outputPinContextMenu" + std::to_string((*link)->OutputPin.Node->GetId()) + std::to_string(i);
                    if (ImGui::Selectable(id.c_str()))
                        linkToDisconnect = (*link).get();

                    ++i;
                }

                if (linkToDisconnect != nullptr) {
                    m_Workspace.DeleteLink(linkToDisconnect);
                    m_IsContextMenuShown = false;
                }

                ImGui::EndMenu();
            }

            if (ImGui::Selectable("Edit description")) {
                m_EditTextPopup.Open("Edit description", pin->Description);
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    void WorkspacePanel::ShowLinkContextMenu(const ImVec2& mousePos, WorkspaceLink* link) {
        ImGui::OpenPopup("linkContextMenu");

        if (ImGui::BeginPopup("linkContextMenu")) {
            if (ImGui::Selectable("Delete")) {
                m_Workspace.DeleteLink(link);
                m_IsContextMenuShown = false;
            }

            ImGui::EndPopup();
        }
    }

    bool WorkspacePanel::IsMouseInsideWorkspace() {
        ImVec2 canvasTopLeft = ImGui::GetCursorScreenPos();    // ImDrawList API uses screen coordinates!
        ImVec2 canvasSize    = ImGui::GetContentRegionAvail(); // Resize canvas to what's available
        ImVec2 canvasBottomRight(canvasTopLeft.x + canvasSize.x, canvasTopLeft.y + canvasSize.y);

        ImVec2 mousePos = ImGui::GetMousePos();

        return (ImGui::IsWindowHovered() || m_IsContextMenuShown) && mousePos.x >= canvasTopLeft.x && mousePos.y >= canvasTopLeft.y && mousePos.x <= canvasBottomRight.x &&
            mousePos.y <= canvasBottomRight.y;
    }
}
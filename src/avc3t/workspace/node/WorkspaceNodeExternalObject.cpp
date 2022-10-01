#include "WorkspaceNodeExternalObject.h"

#include <filesystem>

#include "../../library/SceneObjectLibrary.h"

namespace AVC3T {
    WorkspaceNodeExternalObject::WorkspaceNodeExternalObject(Scene& scene, const std::string& path) :
        WorkspaceNode("External object", {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, {IM_COL32(190, 35, 52, 255)}, std::string_view(),
                      {{"Embed to workspace", &WorkspaceNodeExternalObject::EmbedOptionCallback, &m_CanEmbed, this}}),
        m_Scene(scene), m_SceneObject(nullptr), m_TextArea(nullptr), m_LoadButton(nullptr), m_ObjectFilename(path), m_LoadErrorMessage(), m_CanEmbed(false) {
        InitializeMembers();
        ReloadObject();
    }

    WorkspaceNodeExternalObject::WorkspaceNodeExternalObject(const WorkspaceNodeExternalObject& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText(),
                      {{"Embed to workspace", &WorkspaceNodeExternalObject::EmbedOptionCallback, &m_CanEmbed, this}}),
        m_Scene(other.m_Scene), m_SceneObject(nullptr), m_TextArea(nullptr), m_LoadButton(nullptr), m_ObjectFilename(other.m_ObjectFilename),
        m_LoadErrorMessage(other.m_LoadErrorMessage), m_CanEmbed(false) {
        InitializeMembers();

        m_TextArea->SetText(m_ObjectFilename);

        ReloadObject();
    }

    WorkspaceNodeExternalObject::~WorkspaceNodeExternalObject() noexcept {
        if (m_SceneObject != nullptr)
            m_Scene.RemoveObject(m_SceneObject);
    }

    void WorkspaceNodeExternalObject::InitializeMembers() {
        m_TextArea = std::make_shared<WorkspaceTextArea>(ID::Generate(), false, true);
        m_TextArea->SetSize(s_InputSize);
        m_TextArea->SetText(m_ObjectFilename);

        const ImVec2 contentTopLeft = ImVec2(m_Style.ContentMargin.x, m_Style.ContentMargin.y + m_TitleSize.y);

        m_LoadButton = std::make_shared<WorkspaceButton>("Reload", &WorkspaceNodeExternalObject::ButtonCallback, this);

        const ImVec2& textAreaSize   = m_TextArea->GetSize();
        const ImVec2& loadButtonSize = m_LoadButton->GetSize();

        float         maxHeight = std::max(textAreaSize.y, loadButtonSize.y);

        m_TextArea->SetPosition(ImVec2(contentTopLeft.x, contentTopLeft.y + (maxHeight - textAreaSize.y) / 2));
        m_LoadButton->SetPosition(ImVec2(contentTopLeft.x + textAreaSize.x + s_ItemSpacing, contentTopLeft.y + (maxHeight - loadButtonSize.y) / 2));

        m_Children.push_back(m_TextArea);
        m_Children.push_back(m_LoadButton);
    }

    void WorkspaceNodeExternalObject::Render(WorkspaceRenderContext& context) {
        WorkspaceNode::Render(context);

        if (m_LoadErrorMessage.empty())
            return;

        RenderErrorMessage(context);
    }

    ImVec2 WorkspaceNodeExternalObject::RecalculateContentSize() const {
        // Magic constant for button width
        return ImVec2(s_InputSize.x + s_ItemSpacing + 50, s_InputSize.y);
    }

    void WorkspaceNodeExternalObject::RenderErrorMessage(WorkspaceRenderContext& context) {
        ImVec2 textSize = ImGui::CalcTextSize(m_LoadErrorMessage.c_str());

        ImVec2 min = GetAbsolutePosition(context);
        min.x += context.Origin.x;
        min.y += context.Origin.y - textSize.y - 20;

        const ImGuiStyle& style = ImGui::GetStyle();
        ImVec2            max   = min;
        max.x += textSize.x + style.FramePadding.y * 2.0f;
        max.y += textSize.y + style.FramePadding.x * 2.0f;

        context.DrawList->AddRectFilled(min, max, IM_COL32(150, 50, 50, 225), 0, 0, 5000);

        ImVec2 textPosition = min;
        textPosition.x += 4;
        textPosition.y += 4;

        context.DrawList->AddText(textPosition, IM_COL32(255, 255, 255, 255), m_LoadErrorMessage.c_str(), 5000);
    }

    void WorkspaceNodeExternalObject::Evaluate(double ts) {
        m_CanEmbed = m_SceneObject != nullptr;

        if (m_SceneObject == nullptr)
            return;

        std::shared_ptr<WorkspaceInputPin>& input = m_InputPins[0];

        if (input->Link == nullptr)
            return;

        m_SceneObject->transform.Matrix = *input->Link->OutputPin.Output.Value.mat4;
    }

    void WorkspaceNodeExternalObject::ReloadObject() {
        const std::string& newObjectFilename = m_TextArea->GetText();

        if (m_SceneObject != nullptr)
            m_Scene.RemoveObject(m_SceneObject);

        SceneObjectLibrary::UnloadObject(m_ObjectFilename);
        m_SceneObject = nullptr;

        if (newObjectFilename.empty())
            return;

        try {
            SceneObjectLibrary::LoadObject(newObjectFilename, newObjectFilename);
        } catch (std::string str) {
            m_LoadErrorMessage = str;
            return;
        } catch (const char* message) {
            m_LoadErrorMessage = message;
            return;
        } catch (...) {
            m_LoadErrorMessage = "Could not load object. Unknown error.";
            return;
        }

        m_SceneObject = std::make_shared<SceneObject>(SceneObjectLibrary::CreateObjectCopy(newObjectFilename));
        m_Scene.AddObject(m_SceneObject);

        m_LoadErrorMessage = "";
        m_ObjectFilename   = newObjectFilename;
    }

    std::shared_ptr<WorkspaceNodeEmbeddedObject> WorkspaceNodeExternalObject::CreateEmbeddedObject() {
        std::shared_ptr<SceneObject>                 objectCopy = std::make_shared<SceneObject>(*m_SceneObject);

        std::filesystem::path                        filename = m_ObjectFilename;
        std::shared_ptr<WorkspaceNodeEmbeddedObject> node     = std::make_shared<WorkspaceNodeEmbeddedObject>(m_Scene, filename.filename().string(), objectCopy);

        return node;
    }

    void WorkspaceNodeExternalObject::ButtonCallback(void* userData) {
        WorkspaceNodeExternalObject* instance = static_cast<WorkspaceNodeExternalObject*>(userData);
        instance->ReloadObject();
    }

    InteractionOptionCallbackDemand WorkspaceNodeExternalObject::EmbedOptionCallback(void* data) {
        WorkspaceNodeExternalObject* node = static_cast<WorkspaceNodeExternalObject*>(data);

        return InteractionOptionCallbackDemand(InteractionOptionCallbackDemandType_AddNode, node->CreateEmbeddedObject());
    }
} // namespace AVC3T
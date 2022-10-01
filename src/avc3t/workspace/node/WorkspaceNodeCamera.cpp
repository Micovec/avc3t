#include "WorkspaceNodeCamera.h"
#include "../../scene/WiredCube.h"

namespace AVC3T {
    WorkspaceNodeCamera::WorkspaceNodeCamera(Scene& scene) :
        WorkspaceScalableNode("Camera", {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, {IM_COL32(190, 35, 52, 255)}, ImVec2(110, 110)),
        m_Scene(scene), m_FrameBufferObject(RENDER_WIDTH, RENDER_HEIGHT),
        m_TransparentCubeObject(std::make_shared<SceneObject>(SceneObjectLibrary::CreateObjectCopy(SCENE_OBJECT_TRANSPARENT_CUBE_NAME))),
        m_WiredCubeObject(std::make_shared<WiredCube>()) {
        Initialize();
    }

    WorkspaceNodeCamera::WorkspaceNodeCamera(const WorkspaceNodeCamera& other) :
        WorkspaceScalableNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4), WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, other.m_Style, other.m_BodySize,
                              other.m_Hint->GetHintText()),
        m_Scene(other.m_Scene), m_FrameBufferObject(RENDER_WIDTH, RENDER_HEIGHT),
        m_TransparentCubeObject(std::make_shared<SceneObject>(SceneObjectLibrary::CreateObjectCopy(SCENE_OBJECT_TRANSPARENT_CUBE_NAME))),
        m_WiredCubeObject(std::make_shared<WiredCube>()) {
        Initialize();
    }

    WorkspaceNodeCamera::~WorkspaceNodeCamera() {
        m_Scene.UnmarkCameraObjects({m_TransparentCubeObject, m_WiredCubeObject});
        m_Scene.RemoveObject(m_TransparentCubeObject);
        m_Scene.RemoveObject(m_WiredCubeObject);
    }

    void WorkspaceNodeCamera::Initialize() {
        m_Style.ContentMargin.y = m_Style.ContentMargin.z = m_Style.ContentMargin.x = m_Style.ContentMargin.w = 12;

        m_TransparentCubeObject->sceneObjectFlags |= SceneObjectFlags_DisabledGizmo;
        m_WiredCubeObject->sceneObjectFlags |= SceneObjectFlags_DisabledGizmo;

        m_Scene.AddObject(m_TransparentCubeObject);
        m_Scene.AddObject(m_WiredCubeObject);
        m_Scene.MarkCameraObjects({m_TransparentCubeObject, m_WiredCubeObject});
    }

    void WorkspaceNodeCamera::Render(WorkspaceRenderContext& context) {
        // Render default stuff
        WorkspaceScalableNode::Render(context);

        m_FrameBufferObject.Bind();

        ImVec2 contentSize(m_BodySize.x - m_Style.ContentMargin.x - m_Style.ContentMargin.z, m_BodySize.y - m_Style.ContentMargin.y - m_Style.ContentMargin.w);

        // Render scene into texture
        m_Scene.Render({contentSize.x, contentSize.y}, &m_Camera);

        ImVec2 cursorPosition;
        cursorPosition.x = context.Origin.x + m_Position.x + m_Style.ContentMargin.x;
        cursorPosition.y = context.Origin.y + m_Position.y + m_Style.ContentMargin.y + m_TitleSize.y;

        context.DrawList->AddImage(cursorPosition, (ImTextureID)m_FrameBufferObject.GetTextureID(), contentSize, ImVec2(0, 1), ImVec2(1, 0));

        m_FrameBufferObject.Unbind();
    }

    void WorkspaceNodeCamera::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input0 = m_InputPins[0];
        std::shared_ptr<WorkspaceInputPin>& input1 = m_InputPins[1];

        if (input0->Link != nullptr && input1->Link != nullptr) {
            m_Camera.SetProjectionMatrix(*input0->Link->OutputPin.Output.Value.mat4);
            m_Camera.SetViewMatrix(*input1->Link->OutputPin.Output.Value.mat4);
        }

        glm::mat4 transform = glm::inverse(m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix());

        m_TransparentCubeObject->transform.Matrix = transform;
        m_WiredCubeObject->transform.Matrix       = transform;
    }
} // namespace AVC3T
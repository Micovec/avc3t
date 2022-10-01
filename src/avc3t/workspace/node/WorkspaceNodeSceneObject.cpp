#include "WorkspaceNodeSceneObject.h"

#include "../../library/SceneObjectLibrary.h"

namespace AVC3T {
    WorkspaceNodeSceneObject::WorkspaceNodeSceneObject(Scene& scene, const std::string& sceneObjectName) :
        WorkspaceNode("Object - " + sceneObjectName, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, {IM_COL32(190, 35, 52, 255)},
                      ImVec2(("Object - " + sceneObjectName).size() * 8, 40)),
        m_Scene(scene), m_SceneObject(std::make_shared<SceneObject>(SceneObjectLibrary::CreateObjectCopy(sceneObjectName))), m_SceneObjectName(sceneObjectName) {
        m_Scene.AddObject(m_SceneObject);
    }

    WorkspaceNodeSceneObject::WorkspaceNodeSceneObject(const WorkspaceNodeSceneObject& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()), m_Scene(other.m_Scene),
        m_SceneObject(std::make_shared<SceneObject>(*other.m_SceneObject)), m_SceneObjectName(other.m_SceneObjectName) {
        m_Scene.AddObject(m_SceneObject);
    }

    WorkspaceNodeSceneObject::~WorkspaceNodeSceneObject() noexcept {
        m_Scene.RemoveObject(m_SceneObject);
    }

    void WorkspaceNodeSceneObject::Evaluate(double ts) {
        if (m_SceneObject == nullptr)
            return;

        std::shared_ptr<WorkspaceInputPin>& input = m_InputPins[0];

        if (input->Link == nullptr)
            return;

        m_SceneObject->transform.Matrix = *input->Link->OutputPin.Output.Value.mat4;
    }
} // namespace AVC3T
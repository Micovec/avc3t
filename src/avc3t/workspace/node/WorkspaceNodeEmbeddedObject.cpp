#include "WorkspaceNodeEmbeddedObject.h"

namespace AVC3T {
    WorkspaceNodeEmbeddedObject::WorkspaceNodeEmbeddedObject(Scene& scene, const std::string& name, const std::shared_ptr<SceneObject>& object) :
        WorkspaceNode("Embedded object - " + name, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, {IM_COL32(190, 35, 52, 255)}), m_Scene(scene), m_ObjectName(name),
        m_SceneObject(object) {
        InitializeMembers();
    }

    WorkspaceNodeEmbeddedObject::WorkspaceNodeEmbeddedObject(const WorkspaceNodeEmbeddedObject& other) :
        WorkspaceNode(other.m_Title, {WorkspaceNodeInput(WorkspaceIOType_Mat4)}, {}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()), m_Scene(other.m_Scene),
        m_ObjectName(other.m_ObjectName), m_SceneObject(std::make_shared<SceneObject>(*other.m_SceneObject)) {
        InitializeMembers();
    }

    WorkspaceNodeEmbeddedObject::~WorkspaceNodeEmbeddedObject() {
        m_Scene.RemoveObject(m_SceneObject);
    }

    void WorkspaceNodeEmbeddedObject::InitializeMembers() {
        m_SceneObject->transform.Matrix = glm::mat4(1.0f);
        m_Scene.AddObject(m_SceneObject);
    }

    void WorkspaceNodeEmbeddedObject::Evaluate(double ts) {
        std::shared_ptr<WorkspaceInputPin>& input = m_InputPins[0];

        if (input->Link == nullptr)
            return;

        m_SceneObject->transform.Matrix = *input->Link->OutputPin.Output.Value.mat4;
    }
} // namespace AVC3T
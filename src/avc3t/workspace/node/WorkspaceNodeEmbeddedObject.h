#pragma once

#include "../../scene/Scene.h"

#include "WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeEmbeddedObject : public WorkspaceNode {
      public:
        WorkspaceNodeEmbeddedObject(Scene& scene, const std::string& name, const std::shared_ptr<SceneObject>& object);
        WorkspaceNodeEmbeddedObject(const WorkspaceNodeEmbeddedObject& other);
        ~WorkspaceNodeEmbeddedObject() noexcept;

        void                         Evaluate(double ts) override;

        std::shared_ptr<SceneObject> GetSceneObject() const {
            return m_SceneObject;
        }
        const std::string& GetSceneObjectName() const {
            return m_ObjectName;
        }

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeEmbeddedObject)

      private:
        void InitializeMembers();

      private:
        Scene&                       m_Scene;
        std::string                  m_ObjectName;
        std::shared_ptr<SceneObject> m_SceneObject;
    };
}
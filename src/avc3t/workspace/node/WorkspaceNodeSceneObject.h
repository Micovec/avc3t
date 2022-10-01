#pragma once

#include <functional>
#include <memory>

#include "../../scene/Scene.h"

#include "WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeSceneObject : public WorkspaceNode {
      public:
        WorkspaceNodeSceneObject(Scene& scene, const std::string& sceneObjectName);
        WorkspaceNodeSceneObject(const WorkspaceNodeSceneObject& other);
        ~WorkspaceNodeSceneObject() noexcept;

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeSceneObject)

        std::shared_ptr<SceneObject> GetSceneObject() {
            return m_SceneObject;
        }
        const std::string& GetSceneObjectName() const {
            return m_SceneObjectName;
        }

      private:
        Scene&                       m_Scene;
        std::shared_ptr<SceneObject> m_SceneObject;
        std::string                  m_SceneObjectName;
    };
}
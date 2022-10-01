#pragma once

#include "WorkspaceScalableNode.h"

#include "../../library/SceneObjectLibrary.h"
#include "../../scene/Scene.h"
#include "../../scene/StaticCamera.h"
#include "../../render/FrameBufferObject.h"

namespace AVC3T {
    class WorkspaceNodeCamera : public WorkspaceScalableNode {
      public:
        WorkspaceNodeCamera(Scene& scene);
        WorkspaceNodeCamera(const WorkspaceNodeCamera& other);
        ~WorkspaceNodeCamera();

        void Render(WorkspaceRenderContext& context) override;
        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeCamera)

      private:
        void Initialize();

      private:
        static const std::size_t     RENDER_WIDTH = 500, RENDER_HEIGHT = 500;

        StaticCamera                 m_Camera;
        Scene&                       m_Scene;
        FrameBufferObject            m_FrameBufferObject;

        std::shared_ptr<SceneObject> m_TransparentCubeObject;
        std::shared_ptr<SceneObject> m_WiredCubeObject;
        std::shared_ptr<SceneObject> m_CameraObject;
    };
}
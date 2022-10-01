#pragma once

#include <vector>

#include "EditorCamera.h"
#include "Grid.h"
#include "SceneObject.h"
#include "Gizmo.h"
#include "../render/Renderer.h"
#include "../render/VertexBufferLayout.h"
#include "../mesh/MeshLoader.h"

namespace AVC3T {
    class Scene {
      public:
        Scene();

        void AddObject(std::shared_ptr<SceneObject> object);
        void RemoveObject(std::shared_ptr<SceneObject> object);

        void Render(glm::vec2 screenSize, Camera* camera);

        void MarkCameraObjects(std::pair<std::shared_ptr<SceneObject>, std::shared_ptr<SceneObject>> objects);
        void UnmarkCameraObjects(std::pair<std::shared_ptr<SceneObject>, std::shared_ptr<SceneObject>> objects);

        void EnableCameras();
        void DisableCameras();

      private:
        void RenderObject(const std::shared_ptr<SceneObject>& object, Camera* camera, const std::shared_ptr<Shader>& defaultShader, const std::shared_ptr<Shader>& linesShader,
                          const glm::mat4& PV);
        void SetCamerasEnability(bool enabled);

      private:
        Renderer                                                                           m_Renderer;
        std::vector<std::shared_ptr<SceneObject>>                                          m_SceneObjects;
        std::vector<std::pair<std::shared_ptr<SceneObject>, std::shared_ptr<SceneObject>>> m_CameraObjects;

        Gizmo                                                                              m_Gizmo;
        Grid                                                                               m_Grid;
    };
}
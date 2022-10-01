#pragma once

#include <memory>

#include "../mesh/Mesh.h"
#include "Transform.h"

namespace AVC3T {
    enum SceneObjectFlags_ {
        SceneObjectFlags_None          = 0,
        SceneObjectFlags_Disabled      = 1 << 0,
        SceneObjectFlags_DisabledGizmo = 1 << 1,
        SceneObjectFlags_Transparent   = 1 << 2,
    };

    typedef int SceneObjectFlags;

    struct SceneObject {
        SceneObject(const std::shared_ptr<Mesh>& mesh);
        SceneObject(const std::shared_ptr<Mesh>& mesh, const Transform& transform);
        SceneObject(const SceneObject& other);
        SceneObject(SceneObject&& other);

        std::shared_ptr<Mesh> mesh;
        Transform             transform;
        SceneObjectFlags      sceneObjectFlags;

      private:
        inline void CheckForTransparentTexture();
    };
} // namespace AVC3T
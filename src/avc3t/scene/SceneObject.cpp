#include "SceneObject.h"

#include <utility>

namespace AVC3T {
    SceneObject::SceneObject(const std::shared_ptr<AVC3T::Mesh>& mesh) : mesh(mesh), transform(AVC3T::Transform()), sceneObjectFlags(SceneObjectFlags_None) {
        CheckForTransparentTexture();
    }

    SceneObject::SceneObject(const std::shared_ptr<AVC3T::Mesh>& mesh, const AVC3T::Transform& _transform) :
        mesh(mesh), transform(_transform), sceneObjectFlags(SceneObjectFlags_None) {
        CheckForTransparentTexture();
    }

    SceneObject::SceneObject(const SceneObject& other) : mesh(other.mesh), transform(other.transform), sceneObjectFlags(other.sceneObjectFlags) {}

    SceneObject::SceneObject(SceneObject&& other) : mesh(std::move(other.mesh)), transform(std::move(other.transform)), sceneObjectFlags(other.sceneObjectFlags) {
        CheckForTransparentTexture();
    }

    void SceneObject::CheckForTransparentTexture() {
        if (mesh->GetMaterial().texture == nullptr || !mesh->GetMaterial().texture->ContainsTransparent())
            return;

        sceneObjectFlags |= SceneObjectFlags_Transparent;
    }
} // namespace AVC3T
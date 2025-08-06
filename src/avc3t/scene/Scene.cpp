#include "Scene.h"

#include <iostream>
#include <map>
#include <set>

#include "../library/ShaderLibrary.h"
namespace AVC3T {
    Scene::Scene() : m_Renderer(), m_SceneObjects(), m_CameraObjects(), m_Gizmo(), m_Grid() {}

    void Scene::AddObject(std::shared_ptr<SceneObject> object) {
        m_SceneObjects.push_back(object);
    }

    void Scene::RemoveObject(std::shared_ptr<SceneObject> object) {
        auto it = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), object);
        if (it != m_SceneObjects.end())
            m_SceneObjects.erase(it);
    }

    void Scene::Render(glm::vec2 screenSize, Camera* camera) {
        std::shared_ptr<Shader> defaultShader = ShaderLibrary::GetShader(SHADER_DEFAULT_NAME);
        std::shared_ptr<Shader> linesShader   = ShaderLibrary::GetShader(SHADER_LINES_NAME);

        const glm::mat4         PV             = camera->GetPVMatrix();
        const glm::vec3         cameraPosition = camera->GetProjectionMatrix()[3];

        m_Renderer.Clear();

        // TODO: Cach this?
        std::vector<std::shared_ptr<SceneObject>>               opaqueObjects;
        std::map<float, std::set<std::shared_ptr<SceneObject>>> sortedTransparentObjects;

        // Divide objects to opaque and transparent
        for (auto&& object : m_SceneObjects) {
            if (object->sceneObjectFlags & SceneObjectFlags_Disabled)
                continue;

            if (object->sceneObjectFlags & SceneObjectFlags_Transparent) {
                glm::vec3 objectPosition = object->transform.Matrix[3];
                float     distance       = glm::length(objectPosition - cameraPosition);

                sortedTransparentObjects[distance].insert(object);
                continue;
            }

            opaqueObjects.push_back(object);
        }

        for (auto&& object : opaqueObjects)
            RenderObject(object, camera, defaultShader, linesShader, PV);

        defaultShader->Unbind();

        // Render origin gizmo
        linesShader->Bind();
        linesShader->SetUniformMat4f("u_MVP", PV);
        glLineWidth(3.f);
        // m_Renderer.DrawLines(*m_Gizmo.mesh->GetVertexArray());
        linesShader->Unbind();

        // Render grid
        linesShader->Bind();
        linesShader->SetUniformMat4f("u_MVP", PV);
        glLineWidth(2.f);
        // m_Renderer.DrawLines(*m_Grid.mesh->GetVertexArray());
        linesShader->Unbind();

        for (auto&& [_, objects] : sortedTransparentObjects) {
            for (auto&& object : objects)
                RenderObject(object, camera, defaultShader, linesShader, PV);
        }

        defaultShader->Unbind();
    }

    void Scene::MarkCameraObjects(std::pair<std::shared_ptr<SceneObject>, std::shared_ptr<SceneObject>> objects) {
        m_CameraObjects.push_back(objects);
    }

    void Scene::UnmarkCameraObjects(std::pair<std::shared_ptr<SceneObject>, std::shared_ptr<SceneObject>> objects) {
        auto it = std::find(m_CameraObjects.begin(), m_CameraObjects.end(), objects);
        if (it != m_CameraObjects.end())
            m_CameraObjects.erase(it);
    }

    void Scene::RenderObject(const std::shared_ptr<SceneObject>& object, Camera* camera, const std::shared_ptr<Shader>& defaultShader, const std::shared_ptr<Shader>& linesShader,
                             const glm::mat4& PV) {
        defaultShader->Bind();

        defaultShader->SetUniformVec3("u_DirectionalLight.ambient", glm::vec3(0.6f));
        defaultShader->SetUniformVec3("u_DirectionalLight.diffuse", glm::vec3(0.75f));
        defaultShader->SetUniformVec3("u_DirectionalLight.direction", glm::vec3(1, 1, 1));

        const Material& material = object->mesh->GetMaterial();

        if (material.texture != nullptr)
            material.texture->Bind();

        const glm::mat4 model = object->transform.Matrix;
        const glm::mat4 mvp   = PV * model;

        defaultShader->SetUniformMat4f("u_MVP", mvp);
        defaultShader->SetUniformMat4f("u_ViewMatrix", camera->GetViewMatrix());

        const glm::mat4 modelRotationMatrix = glm::mat4(model[0], model[1], model[2], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        const glm::mat4 normalMatrix        = glm::transpose(glm::inverse(modelRotationMatrix));

        defaultShader->SetUniformMat4f("u_NormalMatrix", normalMatrix);

        defaultShader->SetUniformVec3("u_Material.ambient", object->mesh->GetMaterial().AmbientColor);
        defaultShader->SetUniformVec3("u_Material.diffuse", object->mesh->GetMaterial().DiffuseColor);

        MeshRendering meshRendering = object->mesh->GetMeshRendering();

        switch (meshRendering) {
            case MeshRendering_Triangles: m_Renderer.Draw(*object->mesh->GetVertexArray(), *object->mesh->GetIndexBuffer()); break;

            case MeshRendering_Lines: /*m_Renderer.DrawLines(*object->mesh->GetVertexArray()); */ break;

            default: assert(false);
        }

        if (object->sceneObjectFlags & SceneObjectFlags_DisabledGizmo)
            return;

        // Gizmo
        linesShader->Bind();
        linesShader->SetUniformMat4f("u_MVP", mvp);
        glLineWidth(2.f);
        // m_Renderer.DrawLines(*m_Gizmo.mesh->GetVertexArray());
    }

    void Scene::EnableCameras() {
        SetCamerasEnability(false);
    }

    void Scene::DisableCameras() {
        SetCamerasEnability(true);
    }

    void Scene::SetCamerasEnability(bool disabled) {
        for (auto&& [first, second] : m_CameraObjects) {
            if (disabled) {
                first->sceneObjectFlags |= SceneObjectFlags_Disabled;
                second->sceneObjectFlags |= SceneObjectFlags_Disabled;
                continue;
            }

            first->sceneObjectFlags &= ~SceneObjectFlags_Disabled;
            second->sceneObjectFlags &= ~SceneObjectFlags_Disabled;
        }
    }
} // namespace AVC3T
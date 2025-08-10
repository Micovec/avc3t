#include "SceneObjectLibrary.h"

#include "LibraryRecordNames.h"
#include "LibraryFileValues.h"
#include "../mesh/MeshLoader.h"

namespace AVC3T {
    SceneObjectLibrary& SceneObjectLibrary::GetInstance() {
        static SceneObjectLibrary library;
        return library;
    }

    void SceneObjectLibrary::LoadObject(const std::string& objectName, const std::string& filename) {
        SceneObjectLibrary& instance = GetInstance();
        auto                it       = instance.m_Meshes.find(objectName);

        if (it != instance.m_Meshes.end())
            return;

        instance.m_Meshes.emplace(objectName, std::make_pair<std::shared_ptr<Mesh>, std::size_t>(MeshLoader::LoadObj(filename), 0));
    }

    void SceneObjectLibrary::UnloadObject(const std::string& objectName) {
        SceneObjectLibrary& instance = GetInstance();
        auto                it       = instance.m_Meshes.find(objectName);

        if (it == instance.m_Meshes.end())
            return;

        if (--it->second.second <= 0)
            instance.m_Meshes.erase(it);
    }

    SceneObject SceneObjectLibrary::CreateObjectCopy(const std::string& name) {
        auto& pair = GetInstance().m_Meshes[name];
        pair.second++;

        return SceneObject(pair.first, Transform());
    }

    void SceneObjectLibrary::Init(MemoryIOSystem& memorySystem) {
        GetInstance().m_MemoryIOSystem = &memorySystem;

        LoadObject(SCENE_OBJECT_CONE_NAME, SCENE_OBJECT_CONE_OBJ_FILENAME);
        LoadObject(SCENE_OBJECT_CUBE_NAME, SCENE_OBJECT_CUBE_OBJ_FILENAME);
        LoadObject(SCENE_OBJECT_CYLINDER_NAME, SCENE_OBJECT_CYLINDER_OBJ_FILENAME);
        LoadObject(SCENE_OBJECT_SPHERE_NAME, SCENE_OBJECT_SPHERE_OBJ_FILENAME);
        LoadObject(SCENE_OBJECT_TRANSPARENT_CUBE_NAME, SCENE_OBJECT_TRANSPARENT_CUBE_OBJ_FILENAME);
        LoadObject(SCENE_OBJECT_VECTOR_NAME, SCENE_OBJECT_VECTOR_OBJ_FILENAME);
    }

    void SceneObjectLibrary::Deinit() {
        SceneObjectLibrary& instance = GetInstance();
        instance.m_Meshes.clear();
        instance.m_MemoryIOSystem = nullptr;
    }
}
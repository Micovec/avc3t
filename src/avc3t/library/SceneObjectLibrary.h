#pragma once

#include <memory>
#include <string>
#include <map>

#include "../scene/SceneObject.h"
#include "../io/MemoryIOSystem.h"

namespace AVC3T {
    class SceneObjectLibrary {
      public:
        SceneObjectLibrary(const SceneObjectLibrary& other)                   = delete;
        void                       operator=(const SceneObjectLibrary& other) = delete;

        static SceneObjectLibrary& GetInstance();

        static void                Init(MemoryIOSystem& memorySystem);
        static void                Deinit();
        static void                LoadObject(const std::string& objectName, const std::string& filename);
        static void                UnloadObject(const std::string& objectName);
        static SceneObject         CreateObjectCopy(const std::string& name);

      private:
        SceneObjectLibrary() : m_MemoryIOSystem(nullptr), m_Meshes() {};

        MemoryIOSystem*                                                      m_MemoryIOSystem;

        std::map<std::string, std::pair<std::shared_ptr<Mesh>, std::size_t>> m_Meshes;
    };
}
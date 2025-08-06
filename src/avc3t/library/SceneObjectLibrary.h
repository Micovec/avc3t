#pragma once

#include <memory>
#include <string>
#include <map>

#include "LibraryRecordNames.h"
#include "../scene/SceneObject.h"

namespace AVC3T {
    class SceneObjectLibrary {
      public:
        SceneObjectLibrary(const SceneObjectLibrary& other)                   = delete;
        void                       operator=(const SceneObjectLibrary& other) = delete;

        static SceneObjectLibrary& GetInstance();

        static void                Init();
        static void                Deinit();
        static void                LoadObject(const std::string& objectName, const std::string& objectMtl, const std::string& objectObj, const std::string& objectPng);
        static void                UnloadObject(const std::string& objectName);
        static SceneObject         CreateObjectCopy(const std::string& name);

      private:
        SceneObjectLibrary() : m_Meshes() {};

        std::map<std::string, std::pair<std::shared_ptr<Mesh>, std::size_t>> m_Meshes;
    };
}
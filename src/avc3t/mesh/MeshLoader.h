#pragma once

#include "Mesh.h"
#include "Material.h"

namespace AVC3T {
    class MeshLoader {
      public:
        static void                  Init(MemoryIOSystem& memoryIOSystem);
        static std::shared_ptr<Mesh> LoadObj(const std::string& filename);

      private:
        MeshLoader() {}
        MeshLoader(const MeshLoader&) = delete;

        MeshLoader&        operator=(const MeshLoader&) = delete;

        static MeshLoader& GetInstance();

        // static std::shared_ptr<Texture> LoadTexture(const std::string& filename);

      private:
        MemoryIOSystem* m_MemoryIOSystem;
    };
}
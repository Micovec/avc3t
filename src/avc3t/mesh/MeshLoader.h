#pragma once

#include <assimp/scene.h>

#include "Mesh.h"
#include "Material.h"

namespace AVC3T {
    class MeshLoader {
      public:
        static std::shared_ptr<Mesh> LoadObj(const std::string& filename);

      private:
        static std::shared_ptr<Texture> LoadTexture(const std::string& filename);
    };
}
#pragma once

#include <istream>

#include "Format.h"
#include "ISerializer.h"
#include "../workspace/Workspace.h"

namespace AVC3T {
    class Serializer {
      public:
        void Serialize(Workspace& workspace, Scene& scene, std::istream& stream, SerializeFormat format);
    };
}
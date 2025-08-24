#pragma once

#include "../workspace/Workspace.h"
#include "Format.h"

namespace AVC3T {
    class Deserializer {
      public:
        void Deserialize(const Workspace& workspace, std::ostream& stream, SerializeFormat format);
    };
}
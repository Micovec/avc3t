#pragma once

#include <istream>

#include "../workspace/Workspace.h"

namespace AVC3T {
    class ISerializer {
      public:
        ISerializer() {}
        virtual ~ISerializer() {}
        virtual void Serialize(Workspace& workspace, Scene& scene, std::istream& stream) = 0;
    };
}
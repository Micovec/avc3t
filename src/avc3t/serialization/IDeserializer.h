#pragma once

#include "../workspace/Workspace.h"

namespace AVC3T {
    class IDeserializer {
      public:
        virtual ~IDeserializer()                                                   = default;
        virtual void Deserialize(const Workspace& workspace, std::ostream& stream) = 0;
    };
}
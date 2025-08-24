#pragma once

#include "ISerializer.h"

namespace AVC3T {
    class BinarySerializer : public ISerializer {
      public:
        virtual ~BinarySerializer() {}
        virtual void Serialize(Workspace& workspace, Scene& scene, std::istream& stream) override;
    };
}

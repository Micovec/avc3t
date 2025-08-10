#pragma once

#include "MemoryIOSystem.h"
#include "../library/LibraryRecordNames.h"
#include "../library/LibraryFileValues.h"

namespace AVC3T {
    class MemoryIOSystemMounter {
      public:
        static void Mount(MemoryIOSystem& memoryIOSystem);

      private:
        static void MountObjects(MemoryIOSystem& memoryIOSystem);
        static void MountShaders(MemoryIOSystem& memoryIOSystem);
    };
}

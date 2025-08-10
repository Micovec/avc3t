#include "MemoryFile.h"

#include <cstdlib>

namespace AVC3T {
    MemoryFile::~MemoryFile() {
        free(m_Data);
    }
}
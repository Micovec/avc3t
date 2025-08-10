#include "MemoryIOSystem.h"
#include "MemoryFile.h"
#include <iostream>

namespace AVC3T {
    bool MemoryIOSystem::Exists(const char* pFile) const {
        return m_Files.contains(pFile);
    }

    Assimp::IOStream* MemoryIOSystem::Open(const char* pFile, const char* pMode) {
        MemoryFile& file = EnsureCreated(pFile);

        return new MemoryIOStream(file);
    }

    const MemoryFile& MemoryIOSystem::OpenFile(const std::string& filename) const {
        return m_Files.at(filename);
    }

    MemoryFile& MemoryIOSystem::OpenFile(const std::string& filename) {
        return EnsureCreated(filename);
    }

    void MemoryIOSystem::Close(Assimp::IOStream* pFile) {
        delete pFile;
    }

    MemoryFile& MemoryIOSystem::EnsureCreated(const std::string& filename) {
        auto it = m_Files.find(filename);

        if (it != m_Files.end()) {
            return it->second;
        }

        auto pair = m_Files.emplace(filename, MemoryFile(filename, nullptr, 0, 0));

        return pair.first->second;
    }
}

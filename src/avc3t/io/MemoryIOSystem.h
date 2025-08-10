#pragma once

#include <assimp/IOSystem.hpp>
#include <string>
#include <unordered_map>

#include "MemoryIOStream.h"

namespace AVC3T {
    class MemoryIOSystem : public Assimp::IOSystem {

      public:
        MemoryIOSystem() {}
        MemoryIOSystem(const MemoryIOSystem& other) = delete;

        MemoryIOSystem& operator=(const MemoryIOSystem& other) = delete;

        // -------------------------------------------------------------------
        /** @brief Tests for the existence of a file at the given path.
        *
        * @param pFile Path to the file
        * @return true if there is a file with this path, else false.
        */
        virtual bool Exists(const char* pFile) const override;

        // -------------------------------------------------------------------
        /** @brief Returns the system specific directory separator
        *  @return System specific directory separator
        */
        virtual char getOsSeparator() const override {
            return 0;
        }

        // -------------------------------------------------------------------
        /** @brief Open a new file with a given path.
        *
        *  When the access to the file is finished, call Close() to release
        *  all associated resources (or the virtual dtor of the IOStream).
        *
        *  @param pFile Path to the file
        *  @param pMode Desired file I/O mode. Required are: "wb", "w", "wt",
        *         "rb", "r", "rt".
        *
        *  @return New IOStream interface allowing the lib to access
        *         the underlying file.
        *  @note When implementing this class to provide custom IO handling,
        *  you probably have to supply an own implementation of IOStream as well.
        */
        virtual Assimp::IOStream* Open(const char* pFile, const char* pMode = "rb") override;

        const MemoryFile&         OpenFile(const std::string& filename) const;
        MemoryFile&               OpenFile(const std::string& filename);

        // -------------------------------------------------------------------
        /** @brief Closes the given file and releases all resources
        *    associated with it.
        *  @param pFile The file instance previously created by Open().
        */
        virtual void Close(Assimp::IOStream* pFile) override;

      private:
        MemoryFile& EnsureCreated(const std::string& filename);

      private:
        std::unordered_map<std::string, MemoryFile> m_Files;
    };
}

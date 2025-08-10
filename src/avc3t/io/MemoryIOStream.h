#pragma once

#include <assimp/IOStream.hpp>

#include "MemoryFile.h"

namespace AVC3T {
    class MemoryIOStream : public Assimp::IOStream {
      public:
        MemoryIOStream(MemoryFile& memoryFile);

        // -------------------------------------------------------------------
        /** @brief Read from the file
         *
         * See fread() for more details
         * This fails for write-only files */
        virtual size_t Read(void* pvBuffer, size_t pSize, size_t pCount) override;

        // -------------------------------------------------------------------
        /** @brief Write to the file
         *
         * See fwrite() for more details
         * This fails for read-only files */
        virtual size_t Write(const void* pvBuffer, size_t pSize, size_t pCount) override;

        // -------------------------------------------------------------------
        /** @brief Set the read/write cursor of the file
         *
         * Note that the offset is _negative_ for aiOrigin_END.
         * See fseek() for more details */
        virtual aiReturn Seek(size_t pOffset, aiOrigin pOrigin) override;

        // -------------------------------------------------------------------
        /** @brief Get the current position of the read/write cursor
         *
         * See ftell() for more details */
        virtual size_t Tell() const override;

        // -------------------------------------------------------------------
        /** @brief Returns filesize
         *  Returns the filesize. */
        virtual size_t FileSize() const override;

        // -------------------------------------------------------------------
        /** @brief Flush the contents of the file buffer (for writers)
         *  See fflush() for more details.
         */
        virtual void Flush() override;

      private:
        MemoryFile& m_MemoryFile;

        size_t      m_HeadOffset;
    };
}

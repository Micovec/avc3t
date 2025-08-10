#include "MemoryIOStream.h"

#include <assimp/types.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace AVC3T {
    MemoryIOStream::MemoryIOStream(MemoryFile& memoryFile) : m_MemoryFile(memoryFile), m_HeadOffset(0) {}

    size_t MemoryIOStream::Read(void* pvBuffer, size_t pSize, size_t pCount) {
        size_t availableReadSize   = m_MemoryFile.GetLength() - m_HeadOffset;
        size_t totalNeededReadSize = pSize * pCount;
        size_t readSize            = totalNeededReadSize > availableReadSize ? availableReadSize : totalNeededReadSize;

        std::memcpy(pvBuffer, m_MemoryFile.GetRaw() + m_HeadOffset, readSize);
        m_HeadOffset += readSize;
        return readSize;
    }

    size_t MemoryIOStream::Write(const void* pvBuffer, size_t pSize, size_t pCount) {
        size_t writtenSize = m_MemoryFile.Write((char*)pvBuffer, pSize * pCount);
        m_HeadOffset += writtenSize;

        return writtenSize;
    }

    aiReturn MemoryIOStream::Seek(size_t pOffset, aiOrigin pOrigin) {
        switch (pOrigin) {
            case aiOrigin_CUR: m_HeadOffset += pOffset; break;
            case aiOrigin_SET: m_HeadOffset = pOffset; break;
            case aiOrigin_END: m_HeadOffset = m_MemoryFile.GetLength() - pOffset; break;
            default: return aiReturn_FAILURE;
        }

        return aiReturn_SUCCESS;
    }

    size_t MemoryIOStream::Tell() const {
        return m_HeadOffset;
    }

    size_t MemoryIOStream::FileSize() const {
        return m_MemoryFile.GetLength();
    }

    void MemoryIOStream::Flush() {
        // Nothing to do
    }
}

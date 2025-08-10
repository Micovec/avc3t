#pragma once

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

namespace AVC3T {
    class MemoryFile {
      public:
        MemoryFile(const std::string& name, char* data, size_t length, size_t capacity) : m_Name(name), m_Data(data), m_Length(length), m_Capacity(capacity) {}

        ~MemoryFile();

        template <typename T>
        size_t Write(const T* data, size_t length, size_t position = 0) {
            size_t minimumNeededBufferSize = length + m_Length;

            T*     m_DataT = reinterpret_cast<T*>(m_Data);

            // File was created but not written to
            if (m_Data == nullptr) {
                m_Data = (T*)malloc(minimumNeededBufferSize);

                m_DataT = reinterpret_cast<T*>(m_Data);

                std::copy(data, data + length, m_DataT);
                m_Length   = length;
                m_Capacity = minimumNeededBufferSize;

                return length;
            }

            // Make sure we have enough space to write to
            if (m_Capacity < minimumNeededBufferSize) {
                size_t newBufferSize = m_Capacity;

                while (newBufferSize < minimumNeededBufferSize)
                    newBufferSize *= 2;

                T* newBuffer = (T*)malloc(newBufferSize);

                std::copy(m_DataT, m_DataT + length, newBuffer);

                delete[] m_DataT;

                m_Data     = newBuffer;
                m_Capacity = newBufferSize;

                m_DataT = reinterpret_cast<T*>(m_Data);
            }

            // If we are writing in the middle of the file then move the necessary stuff inside the buffer
            if (position > 0 && position != m_Length)
                std::copy_backward(m_DataT + position, m_DataT + m_Length - position, m_DataT + position + length);

            std::copy(data, data + length, m_DataT + position);

            m_Length += length;

            return length;
        }

        size_t WriteText(const char* data, size_t position = 0) {
            return Write<char>(data, std::strlen(data), position);
        }

        size_t WriteRaw(const unsigned char* data, size_t length, size_t position = 0) {
            return Write<unsigned char>(data, length, position);
        }

        const char* GetText() const {
            return reinterpret_cast<const char*>(m_Data);
        }

        const unsigned char* GetRaw() const {
            return reinterpret_cast<const unsigned char*>(m_Data);
        }

        size_t GetLength() const {
            return m_Length;
        }

      private:
        std::string m_Name;
        void*       m_Data;
        size_t      m_Length;
        size_t      m_Capacity;
    };
}

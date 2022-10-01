#pragma once

#include <cstddef>

namespace AVC3T {
    // Very primitive identificator generator
    class ID {
      public:
        static std::size_t Generate() {
            // First retrieved ID MUST BE 1, otherwise deserialization/serialization won't work
            return ++GetInstance().m_CurrentId;
        }

        static void Reset() {
            GetInstance().m_CurrentId = 0;
        }

      private:
        static ID& GetInstance() {
            static ID id;
            return id;
        }

      private:
        ID() : m_CurrentId(0) {}
        ID(const ID&) = delete;
        ID(ID&&)      = delete;

        std::size_t m_CurrentId;
    };
}
#pragma once

#include <cstdlib>

namespace AVC3T {
    class BitUtils {
      public:
        static std::size_t BitCount(int number) {
            std::size_t count = 0;

            for (std::size_t i = 0; i < sizeof(number) * 8; ++i)
                count += number & (1 << i);

            return count;
        }
    };
}
#pragma once

#include <string>
#include <vector>

namespace AVC3T {
    class StringUtils {
      public:
        static std::vector<std::string> Split(const std::string& str, char delimiter);
        static void                     ReplaceAll(std::string& str, const std::string& from, const std::string& to);
    };
}
#include "StringUtils.h"

#include <cstdint>

namespace AVC3T {
    std::vector<std::string> StringUtils::Split(const std::string& str, char delimiter) {
        std::vector<std::string> splitted;

        std::size_t              lastIndex = 0;
        for (std::size_t i = 0; i < str.size(); ++i) {
            if (str[i] == delimiter) {
                splitted.push_back(str.substr(lastIndex, i - lastIndex));
                lastIndex = i + 1;
            }
        }

        return splitted;
    }

    void StringUtils::ReplaceAll(std::string& str, const std::string& from, const std::string& to) {
        if (from.empty())
            return;

        size_t startPosition = 0;
        while ((startPosition = str.find(from, startPosition)) != std::string::npos) {
            str.replace(startPosition, from.length(), to);
            startPosition += to.length();
        }
    }
}
#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace AVC3T {
    class SerDerTab {
      public:
        SerDerTab() : m_TabLength(Tab.length()), m_Count(0) {}

        friend std::ostream& operator<<(std::ostream& stream, const SerDerTab& tabs) {
            for (std::size_t i = 0; i < tabs.m_Count; ++i)
                stream << Tab;

            return stream;
        }

        friend std::istream& operator>>(std::istream& stream, const SerDerTab& tabs) {
            for (std::size_t i = 0; i < tabs.m_Count; ++i) {
                for (std::size_t k = 0; k < tabs.m_TabLength; ++k) {
                    char c;
                    stream >> c;

                    if (c != Tab[k])
                        throw std::length_error("Invalid tab size");
                }
            }

            return stream;
        }

        int operator++() {
            return ++m_Count;
        }

        int operator++(int) {
            return m_Count++;
        }

        int operator--() {
            return --m_Count;
        }

        int operator--(int) {
            return m_Count--;
        }

        int operator+=(int c) {
            m_Count += c;
            return m_Count;
        }

        int operator+(int c) {
            m_Count += c;
            return m_Count;
        }

        int operator-=(int c) {
            m_Count -= c;
            return m_Count;
        }

        int operator-(int c) {
            m_Count -= c;
            return m_Count;
        }

        int operator=(int c) {
            m_Count = c;
            return m_Count;
        }

      public:
        static constexpr std::string_view Tab = "    ";

      private:
        std::size_t m_TabLength;
        std::size_t m_Count;
    };
} // namespace AVC3T
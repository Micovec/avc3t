#pragma once

#include <cstring>
#include <istream>
#include <stdexcept>
#include <string>

namespace AVC3T {
    class StreamExpect {
      public:
        StreamExpect& Expect(const char* text) {
            m_Text = text;
            m_Size = std::strlen(text);

            return *this;
        }

        StreamExpect& ExpectNewLine(std::istream& stream) {
            char c = stream.peek();

            if (c == '\r') {
                stream.get();
                c = stream.peek();
            }

            if (c == '\n') {
                stream.get();
                return *this;
            }

            std::string message = "Expected new line character. Got '";
            std::string line;

            std::getline(stream, line);

            message += line;
            message += "' instead.";

            throw std::runtime_error(message);
        }

        friend std::istream& operator>>(std::istream& stream, const StreamExpect& expect) {
            for (std::size_t i = 0; i < expect.m_Size; ++i) {
                char c;
                stream >> c;

                if (c != expect.m_Text[i]) {
                    std::string message = "Expected '";
                    message += expect.m_Text[i];
                    message += "' recieved '";
                    message += c;
                    message += "' instead.";

                    throw std::runtime_error(message);
                }
            }

            return stream;
        }

      private:
        const char* m_Text;
        std::size_t m_Size;
    };
} // namespace AVC3T
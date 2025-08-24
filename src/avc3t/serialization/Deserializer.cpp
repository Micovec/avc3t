#include "Deserializer.h"

#include "BinaryDeserializer.h"
#include "TextDeserializer.h"
#include <memory>

namespace AVC3T {
    void Deserializer::Deserialize(const Workspace& workspace, std::ostream& stream, SerializeFormat format) {
        std::unique_ptr<IDeserializer> deserializer;

        switch (format) {
            case SerializeFormat::Binary: deserializer = std::make_unique<BinaryDeserializer>(); break;
            case SerializeFormat::Text: deserializer = std::make_unique<TextDeserializer>(); break;
        }

        deserializer->Deserialize(workspace, stream);
    }
}
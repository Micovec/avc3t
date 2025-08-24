#include "Serializer.h"
#include "BinarySerializer.h"
#include "SerDerConstants.h"
#include "TextSerializer.h"
#include <memory>
#include <stdexcept>

namespace AVC3T {
    void Serializer::Serialize(Workspace& workspace, Scene& scene, std::istream& stream, SerializeFormat format) {
        std::unique_ptr<ISerializer> serializer;

        switch (format) {
            case SerializeFormat::Binary: serializer = std::make_unique<BinarySerializer>(); break;
            case SerializeFormat::Text: serializer = std::make_unique<TextSerializer>(); break;
        }

        serializer->Serialize(workspace, scene, stream);
    }
}
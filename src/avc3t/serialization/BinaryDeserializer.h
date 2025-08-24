#pragma once

#include "IDeserializer.h"

namespace AVC3T {
    class BinaryDeserializer : public IDeserializer {
      public:
        virtual void Deserialize(const Workspace& workspace, std::ostream& stream) override;

      private:
        void DeserializeElement(const std::shared_ptr<WorkspaceElement>& element, std::ostream& stream);
        void DeserializeNode(WorkspaceNode& node, const char* name, std::ostream& stream);
    };
}
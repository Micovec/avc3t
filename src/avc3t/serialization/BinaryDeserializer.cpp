#include "BinaryDeserializer.h"
#include "SerDerConstants.h"
#include "WorkspaceNodeBinaryStore.h"

#define DESERIALIZE_NODE_IF_TYPE(type, node, stream)                                                                                                                               \
    if (type* castedNode = dynamic_cast<type*>(node)) {                                                                                                                            \
        DeserializeNode(*castedNode, type, stream);                                                                                                                                \
        return;                                                                                                                                                                    \
    }

namespace AVC3T {
    void BinaryDeserializer::Deserialize(const Workspace& workspace, std::ostream& stream) {
        for (const auto& [_, elements] : workspace.GetElements()) {
            for (const auto& element : elements) {
                DeserializeElement(element, stream);
            }
        }
    }

    void BinaryDeserializer::DeserializeElement(const std::shared_ptr<WorkspaceElement>& element, std::ostream& stream) {
        WorkspaceElement* elementPtr = element.get();
        if (dynamic_cast<WorkspaceLink*>(elementPtr))
            return;

        DESERIALIZE_NODE_IF_TYPE(WorkspaceNodeFloatValue, elementPtr, stream);
    }

    void BinaryDeserializer::DeserializeNode(WorkspaceNode& node, const char* name, std::ostream& stream) {
        size_t type = WorkspaceNodeBinaryStore::GetNodeType(name);
    }
}

#undef DESERIALIZE_NODE_IF_TYPE

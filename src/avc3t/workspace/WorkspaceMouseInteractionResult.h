#pragma once

#include <memory>
#include <string>
#include <variant>

namespace AVC3T {
    typedef int WorkspaceInteractionFlags;
    enum WorkspaceInteractionFlags_ {
        WorkspaceInteractionFlags_None     = 0,
        WorkspaceInteractionFlags_Hovered  = 1 << 0,
        WorkspaceInteractionFlags_Selected = 1 << 1
    };

    typedef int InteractedElementType;
    enum InteractedElementType_ {
        InteractedElementType_None      = 0,
        InteractedElementType_NodeBar   = 1 << 0,
        InteractedElementType_NodeBody  = 1 << 1,
        InteractedElementType_InputPin  = 1 << 2,
        InteractedElementType_OutputPin = 1 << 3,
        InteractedElementType_Link      = 1 << 4,
        InteractedElementType_Input     = 1 << 5,
        InteractedElementType_Element   = 1 << 6, // If no other workspace elements have been interacted then this value is used
    };

    typedef int InteractionOptionCallbackDemandType;
    enum InteractionOptionCallbackDemandType_ {
        InteractionOptionCallbackDemandType_None    = 0,
        InteractionOptionCallbackDemandType_AddNode = 1
    };

    class WorkspaceNode;
    struct WorkspaceInputPin;
    struct WorkspaceOutputPin;
    struct WorkspaceLink;
    class WorkspaceElement;

    using InteractionOptionCallbackDemandValue = std::variant<std::shared_ptr<WorkspaceNode>, std::shared_ptr<WorkspaceLink>>;

    struct InteractionOptionCallbackDemand {
        InteractionOptionCallbackDemand() : DemandType(InteractionOptionCallbackDemandType_None), Value(static_cast<std::shared_ptr<WorkspaceNode>>(nullptr)) {}

        InteractionOptionCallbackDemand(InteractionOptionCallbackDemandType demandType, std::shared_ptr<WorkspaceNode> node) : DemandType(demandType), Value(node) {}

        InteractionOptionCallbackDemand(InteractionOptionCallbackDemandType demandType, std::shared_ptr<WorkspaceLink> link) : DemandType(demandType), Value(link) {}

        InteractionOptionCallbackDemandType  DemandType;
        InteractionOptionCallbackDemandValue Value;
    };

    typedef InteractionOptionCallbackDemand (*WorkspaceMouseInteractionOptionCallback)(void* data);

    struct WorkspaceMouseInteractionOption {
        WorkspaceMouseInteractionOption(const std::string_view& label, WorkspaceMouseInteractionOptionCallback callback, bool* enabled = nullptr, void* data = nullptr,
                                        const std::vector<WorkspaceMouseInteractionOption>& suboptions = {}) :
            Label(label), Callback(callback), Enabled(enabled), Data(data), Suboptions(suboptions) {}

        WorkspaceMouseInteractionOption(const WorkspaceMouseInteractionOption& other) = default;

        WorkspaceMouseInteractionOption& operator=(const WorkspaceMouseInteractionOption& other) {
            if (this == &other)
                return *this;

            Label      = other.Label;
            Callback   = other.Callback;
            Enabled    = other.Enabled;
            Data       = other.Data;
            Suboptions = other.Suboptions;

            return *this;
        }

        std::string_view                             Label;
        WorkspaceMouseInteractionOptionCallback      Callback;
        bool*                                        Enabled;
        void*                                        Data;

        std::vector<WorkspaceMouseInteractionOption> Suboptions;
    };

    using InteractedElementValue = std::variant<WorkspaceNode*, WorkspaceInputPin*, WorkspaceOutputPin*, WorkspaceLink*, WorkspaceElement*>;

    struct WorkspaceMouseInteractionResult {
        WorkspaceMouseInteractionResult() : Value(), Type(InteractedElementType_None), Options() {}

        WorkspaceMouseInteractionResult(const WorkspaceMouseInteractionResult& other) : Value(other.Value), Type(other.Type), Options(other.Options) {}

        WorkspaceMouseInteractionResult(InteractedElementValue value, InteractedElementType type, const std::vector<WorkspaceMouseInteractionOption>& options = {}) :
            Value(value), Type(type), Options(options) {}

        WorkspaceMouseInteractionResult& operator=(const WorkspaceMouseInteractionResult& other) {
            if (this == &other)
                return *this;

            Value   = other.Value;
            Type    = other.Type;
            Options = other.Options;

            return *this;
        }

      public:
        InteractedElementValue                       Value;
        InteractedElementType                        Type;
        std::vector<WorkspaceMouseInteractionOption> Options;
    };
}
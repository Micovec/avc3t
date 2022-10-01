#pragma once

#include <glm/glm.hpp>

#include "WorkspaceElement.h"
#include "imgui.h"

namespace AVC3T {
    enum WorkspaceIOType_ {
        WorkspaceIOType_None  = 0,
        WorkspaceIOType_Bool  = 1 << 0,
        WorkspaceIOType_Float = 1 << 1,
        WorkspaceIOType_Vec3  = 1 << 2,
        WorkspaceIOType_Vec4  = 1 << 3,
        WorkspaceIOType_Mat4  = 1 << 4,
        WorkspaceIOType_Quat  = 1 << 5,
    };

    typedef int WorkspaceIOType;

    union WorkspaceIOValue {
        WorkspaceIOValue() : b(nullptr) {}

        WorkspaceIOValue(bool* bool_ptr) : b(bool_ptr) {}

        WorkspaceIOValue(float* float_ptr) : f(float_ptr) {}

        WorkspaceIOValue(glm::vec3* vec3_ptr) : vec3(vec3_ptr) {}

        WorkspaceIOValue(glm::vec4* vec4_ptr) : vec4(vec4_ptr) {}

        WorkspaceIOValue(glm::quat* quat_ptr) : quat(quat_ptr) {}

        WorkspaceIOValue(glm::mat4* mat4_ptr) : mat4(mat4_ptr) {}

        bool*      b;
        float*     f;
        glm::vec3* vec3;
        glm::vec4* vec4;
        glm::quat* quat;
        glm::mat4* mat4;
    };

    // input having only type and output having the actual value and type plus on
    // top of that a locked indices value
    struct WorkspaceNodeInput {
        WorkspaceNodeInput(const WorkspaceIOType& type, std::string_view description = "") : Type(type), Description(description) {}

        WorkspaceIOType        Type;
        const std::string_view Description;
    };

    struct WorkspaceNodeOutput {
        WorkspaceNodeOutput(const WorkspaceIOType& type, WorkspaceIOValue value, std::uint16_t lockedIndices = 0, std::string_view description = "") :
            Type(type), Value(value), Disabled(false), LockedIndices(lockedIndices), Description(description) {}

        WorkspaceIOType  Type;
        WorkspaceIOValue Value;

        bool             Disabled;

        // Each bit in this variable represents a locked float input in
        // glm::value_ptr(Value) order. If bit is set to 1 then it is locked For
        // example: 3d vector has set bits ...011 meaning x and y are locked whereas z
        // is not
        const std::uint16_t    LockedIndices;
        const std::string_view Description;
    };

    struct WorkspaceLink;

    struct WorkspacePin : public WorkspaceElement {
        WorkspacePin(WorkspaceNode* node, WorkspaceIOType type, InteractedElementType interactedType, std::string_view description) :
            WorkspaceElement(), Node(node), Description(description), Type(type), m_InteractedType(interactedType), m_TextSize(), m_Margin() {
            RecalculateSize();
        }

        virtual void Evaluate(double ts) override {}

        virtual void Render(WorkspaceRenderContext& context) override {
            std::vector<ImColor> colors;

            // TODO define pin colors somewhere else, header file or something
            if (Type & WorkspaceIOType_Bool)
                colors.push_back(IM_COL32(190, 80, 80, 255));

            if (Type & WorkspaceIOType_Float)
                colors.push_back(IM_COL32(190, 190, 0, 255));

            if (Type & WorkspaceIOType_Vec3)
                colors.push_back(IM_COL32(46, 121, 235, 255));

            if (Type & WorkspaceIOType_Vec4)
                colors.push_back(IM_COL32(217, 22, 224, 255));

            if (Type & WorkspaceIOType_Mat4)
                colors.push_back(IM_COL32(90, 158, 42, 255));

            if (Type & WorkspaceIOType_Quat)
                colors.push_back(IM_COL32(224, 116, 22, 255));

            if (HasFlags(WorkspaceInteractionFlags_Hovered)) {
                for (auto&& color : colors) {
                    color.Value.x += 12;
                    color.Value.y += 12;
                    color.Value.z += 12;
                }
            }

            ImVec2             position = GetAbsolutePosition(context);

            std::vector<ImU32> colorsInts;
            for (auto&& color : colors)
                colorsInts.push_back(ImGui::ColorConvertFloat4ToU32(color));

            RecalculateSize();
            context.DrawList->AddCircleFilledColors(position, s_Size, colorsInts, s_Segments);
        }

      public:
        WorkspaceNode*  Node;
        std::string     Description;

        WorkspaceIOType Type;

      protected:
        void RecalculateSize() {
            m_TextSize = ImGui::CalcTextSize(Description.data());

            m_Margin.x = m_TextSize.x > 0 ? s_Size * 2 : 0;
            m_Margin.z = m_TextSize.x > 0 ? s_Size * 2 : 0;

            m_Size.x = std::max(s_Size * 2, m_TextSize.x + m_Margin.x + m_Margin.z);
            m_Size.y = std::max(s_Size * 2, m_TextSize.y + m_Margin.y + m_Margin.w);
        }

      protected:
        const InteractedElementType m_InteractedType;

        ImVec2                      m_TextSize;
        ImVec4                      m_Margin;

        constexpr static float      s_Size     = 5.5f;
        constexpr static int        s_Segments = 10;
    };

    struct WorkspaceInputPin : public WorkspacePin {
        // TODO: workspace pin size is constant defined in constructor
        WorkspaceInputPin(const WorkspaceNodeInput& input, WorkspaceNode* node, std::string_view description = "") :
            WorkspacePin(node, input.Type, InteractedElementType_InputPin, description), Input(input), Link(nullptr) {}

        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_InputPin);
            return WorkspaceMouseInteractionResult();
        }

        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_InputPin);
            return WorkspaceMouseInteractionResult();
        }

        // TODO code duplication
        virtual WorkspaceMouseInteractionResult MouseReleased(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_InputPin);
            return WorkspaceMouseInteractionResult();
        }

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size)) {
                AddFlags(WorkspaceInteractionFlags_Hovered);
                return WorkspaceMouseInteractionResult(this, InteractedElementType_InputPin);
            }

            RemoveFlags(WorkspaceInteractionFlags_Hovered);
            return WorkspaceMouseInteractionResult();
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            WorkspacePin::Render(context);

            ImVec2 position = GetAbsolutePosition(context);
            position.x += m_Margin.x;
            position.y -= m_TextSize.y / 2;

            context.DrawList->AddText(position, IM_COL32(240, 240, 240, 255), Description.data());
        }

        inline bool DataAvailable() {
            return Link != nullptr;
        }

        WorkspaceNodeInput             Input;
        std::shared_ptr<WorkspaceLink> Link;
    };

    struct WorkspaceOutputPin : public WorkspacePin {
        // TODO: workspace pin size is constant defined in constructor
        WorkspaceOutputPin(const WorkspaceNodeOutput& output, WorkspaceNode* node, std::string_view description = "") :
            WorkspacePin(node, output.Type, InteractedElementType_OutputPin, description), Output(output), Links() {}

        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_OutputPin);
            return WorkspaceMouseInteractionResult();
        }

        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_OutputPin);
            return WorkspaceMouseInteractionResult();
        }

        virtual WorkspaceMouseInteractionResult MouseReleased(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_OutputPin);
            return WorkspaceMouseInteractionResult();
        }

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            if (!interaction.Handled && IsPositionInsideCircle(interaction.mousePosition, ImVec2(0, 0), s_Size)) {
                AddFlags(WorkspaceInteractionFlags_Hovered);
                return WorkspaceMouseInteractionResult(this, InteractedElementType_OutputPin);
            }

            RemoveFlags(WorkspaceInteractionFlags_Hovered);
            return WorkspaceMouseInteractionResult();
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            WorkspacePin::Render(context);

            ImVec2 position = GetAbsolutePosition(context);
            position.x -= m_Margin.z + m_TextSize.x;
            position.y -= m_TextSize.y / 2;

            context.DrawList->AddText(position, IM_COL32(240, 240, 240, 255), Description.data());
        }

        WorkspaceNodeOutput                         Output;
        std::vector<std::shared_ptr<WorkspaceLink>> Links;
    };
} // namespace AVC3T
#pragma once

#include <memory>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <imgui/imgui.h>

#include "WorkspaceNodeStyle.h"
#include "../../ui/MouseButton.h"
#include "../../utils/ID.h"

#include "../WorkspaceElement.h"
#include "../WorkspaceHint.h"
#include "../WorkspaceLink.h"
#include "../WorkspaceInput.h"

#define GENERATE_NODE_COPY_METHOD(type)                                                                                                                                            \
    virtual inline std::shared_ptr<WorkspaceNode> Copy() const override {                                                                                                          \
        return std::make_shared<type>(*this);                                                                                                                                      \
    }

namespace AVC3T {
    class WorkspaceNode : public WorkspaceElement {
      public:
        WorkspaceNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs, const WorkspaceNodeStyle& style,
                      std::string_view hint = std::string_view(), const std::vector<WorkspaceMouseInteractionOption>& additionalOptions = {});
        WorkspaceNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs, const WorkspaceNodeStyle& style,
                      const ImVec2& bodySize, std::string_view hint = std::string_view(), const std::vector<WorkspaceMouseInteractionOption>& additionalOptions = {});
        WorkspaceNode(const WorkspaceNode& other) :
            WorkspaceElement(other), m_Id(ID::Generate()), m_Title(other.m_Title), m_Style(other.m_Style), m_BodySize(other.m_BodySize), m_InputPins(), m_OutputPins(),
            m_Hint(nullptr) {
            std::vector<WorkspaceNodeInput> inputs;
            for (auto&& input : other.m_InputPins)
                inputs.push_back(input->Input);

            std::vector<WorkspaceNodeOutput> outputs;
            for (auto&& output : other.m_OutputPins)
                outputs.push_back(output->Output);

            Initialize(inputs, outputs, other.m_Hint->GetHintText());
        }

        virtual ~WorkspaceNode() {}

        virtual void                                  Render(WorkspaceRenderContext& context) override;
        virtual void                                  Evaluate(double ts) override = 0;

        virtual inline std::shared_ptr<WorkspaceNode> Copy() const = 0;

        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override;
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction) override;
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MouseReleased(const WorkspaceMouseInteraction& interaction) override;
        // Position is relative to node position
        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override;

        std::size_t                             GetId() const {
            return m_Id;
        }
        std::string& GetTitle() {
            return m_Title;
        }

        std::vector<std::shared_ptr<WorkspaceInputPin>>& GetInputPins() {
            return m_InputPins;
        }
        std::vector<std::shared_ptr<WorkspaceOutputPin>>& GetOutputPins() {
            return m_OutputPins;
        }

        ImVec2 GetSize() const {
            return ImVec2(m_BodySize.x, m_BodySize.y + m_TitleSize.y);
        }
        void SetTitle(const std::string& title) {
            m_Title = title;
        }

        const WorkspaceNodeStyle& GetStyle() const {
            return m_Style;
        }

      protected:
        virtual ImVec2 RecalculateContentSize() const;

      protected:
        std::size_t                                      m_Id;

        std::string                                      m_Title;
        WorkspaceNodeStyle                               m_Style;

        ImVec2                                           m_TitleSize;
        ImVec2                                           m_BodySize;

        std::vector<std::shared_ptr<WorkspaceInputPin>>  m_InputPins;
        std::vector<std::shared_ptr<WorkspaceOutputPin>> m_OutputPins;
        std::vector<std::shared_ptr<WorkspaceInput>>     m_Inputs;

        std::shared_ptr<WorkspaceHint>                   m_Hint;

        std::vector<WorkspaceMouseInteractionOption>     m_AdditionalOptions;

      private:
        void Initialize(const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs, const std::string_view& hint);

        void RenderBody(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, WorkspaceRenderContext& context, float rounding = 4.0f,
                        ImDrawFlags flags = ImDrawFlags_None);
        void RenderTopBar(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, WorkspaceRenderContext& context, float rounding = 4.0f,
                          ImDrawFlags flags = ImDrawFlags_RoundCornersTop);
        void RenderDescription(const ImVec2& position, ImColor color, const char* text, WorkspaceRenderContext& context);

        void AddPins(const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs);
        void RecalculateSizes();
        void RecalculatePinPositions();
        void RecalculateInputPositions();
        void RecalculateHintPosition();
        void RecalculateContentMargin();

        void AddWorkspaceInputs(const std::vector<std::shared_ptr<WorkspaceOutputPin>>& outputPins);

        inline WorkspaceMouseInteractionResult GetGeneralMouseInteraction(const WorkspaceMouseInteraction& interaction);
    };
}
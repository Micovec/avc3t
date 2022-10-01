#include "WorkspaceNode.h"
#include "imgui.h"

namespace AVC3T {
    WorkspaceNode::WorkspaceNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                                 const WorkspaceNodeStyle& style, std::string_view hint, const std::vector<WorkspaceMouseInteractionOption>& additionalOptions) :
        m_Id(ID::Generate()), m_Title(title), m_Style(style), m_BodySize(0, 0), m_InputPins(), m_OutputPins(), m_Inputs(), m_Hint(nullptr), m_AdditionalOptions(additionalOptions) {
        Initialize(inputs, outputs, hint);
    }

    WorkspaceNode::WorkspaceNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                                 const WorkspaceNodeStyle& style, const ImVec2& bodySize, std::string_view hint,
                                 const std::vector<WorkspaceMouseInteractionOption>& additionalOptions) :
        m_Id(ID::Generate()), m_Title(title), m_Style(style), m_BodySize(bodySize), m_InputPins(), m_OutputPins(), m_Inputs(), m_Hint(nullptr),
        m_AdditionalOptions(additionalOptions) {
        Initialize(inputs, outputs, hint);
    }

    void WorkspaceNode::Initialize(const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs, const std::string_view& hint) {
        AddPins(inputs, outputs);
        AddWorkspaceInputs(m_OutputPins);

        m_Hint = std::make_shared<WorkspaceHint>(hint);
        m_Hint->SetParent(this);
        m_Children.push_back(m_Hint);

        RecalculateContentMargin();
        RecalculateSizes();
    }

    void WorkspaceNode::Render(WorkspaceRenderContext& context) {
        RecalculateContentMargin();
        RecalculateSizes();
        RecalculatePinPositions();
        RecalculateInputPositions();
        RecalculateHintPosition();

        const ImVec2 topLeft     = ImVec2(context.Origin.x + m_Position.x, context.Origin.y + m_Position.y);
        const ImVec2 bottomRight = ImVec2(topLeft.x + m_BodySize.x, topLeft.y + m_BodySize.y + m_TitleSize.y);

        // Body
        ImColor backgroundColor      = m_Style.BackgroundColor;
        ImColor titleBackgroundColor = m_Style.BarBackgroundColor;

        if (HasFlags(WorkspaceInteractionFlags_Hovered)) {
            backgroundColor      = m_Style.BackgroundColorHovered;
            titleBackgroundColor = m_Style.BarBackgroundColorHovered;
        } else if (HasFlags(WorkspaceInteractionFlags_Selected)) {
            backgroundColor      = m_Style.BackgroundColorSelected;
            titleBackgroundColor = m_Style.BarBackgroundColorSelected;
        }

        RenderBody(topLeft, bottomRight, backgroundColor, context);

        // Top bar
        RenderTopBar(topLeft, ImVec2(bottomRight.x, topLeft.y + m_TitleSize.y), titleBackgroundColor, context);

        ImVec2 descriptionPosition(topLeft.x + m_Style.TitleMargin.x, topLeft.y + m_Style.TitleMargin.y);
        RenderDescription(descriptionPosition, m_Style.TitleTextColor, m_Title.c_str(), context);

        if (HasFlags(WorkspaceInteractionFlags_Selected))
            context.DrawList->AddRect(topLeft, bottomRight, IM_COL32(17, 205, 247, 128), 4, 0, 1.5f);

        WorkspaceRenderContext childrenContext(context, m_Position);
        RenderChildren(childrenContext);
    }

    void WorkspaceNode::RenderBody(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, WorkspaceRenderContext& context, float rounding, ImDrawFlags flags) {
        context.DrawList->AddRectFilled(topLeft, bottomRight, color, rounding, flags);
    }

    void WorkspaceNode::RenderTopBar(const ImVec2& topLeft, const ImVec2& bottomRight, ImColor color, WorkspaceRenderContext& context, float rounding, ImDrawFlags flags) {
        context.DrawList->AddRectFilled(topLeft, bottomRight, color, rounding, flags);
    }

    void WorkspaceNode::RenderDescription(const ImVec2& position, ImColor color, const char* text, WorkspaceRenderContext& context) {
        context.DrawList->AddText(position, color, text);
    }

    WorkspaceMouseInteractionResult WorkspaceNode::MousePressed(const WorkspaceMouseInteraction& interaction) {
        WorkspaceMouseInteractionResult baseResult = WorkspaceElement::MousePressed(interaction);

        if (baseResult.Type != InteractedElementType_None)
            return baseResult;

        return GetGeneralMouseInteraction(interaction);
    }

    WorkspaceMouseInteractionResult WorkspaceNode::MouseClicked(const WorkspaceMouseInteraction& interaction) {
        WorkspaceMouseInteractionResult baseResult = WorkspaceElement::MouseClicked(interaction);

        if (baseResult.Type != InteractedElementType_None)
            return baseResult;

        return GetGeneralMouseInteraction(interaction);
    }

    WorkspaceMouseInteractionResult WorkspaceNode::MouseReleased(const WorkspaceMouseInteraction& interaction) {
        WorkspaceMouseInteractionResult baseResult = WorkspaceElement::MouseReleased(interaction);

        if (baseResult.Type != InteractedElementType_None)
            return baseResult;

        return GetGeneralMouseInteraction(interaction);
    }

    WorkspaceMouseInteractionResult WorkspaceNode::MousePositionUpdate(const WorkspaceMouseInteraction& interaction) {
        WorkspaceMouseInteractionResult baseResult = WorkspaceElement::MousePositionUpdate(interaction);

        if ((baseResult.Type != InteractedElementType_None && baseResult.Type != InteractedElementType_Input) || interaction.Handled) {
            RemoveFlags(WorkspaceInteractionFlags_Hovered);
            return baseResult;
        }

        InteractedElementType type = InteractedElementType_None;
        ImVec2                barMax(GetSize().x, m_TitleSize.y);

        if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), barMax))
            type = InteractedElementType_NodeBar;
        else if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, m_TitleSize.y), GetSize()))
            type = InteractedElementType_NodeBody;

        if (type != InteractedElementType_None) {
            AddFlags(WorkspaceInteractionFlags_Hovered);

            if (baseResult.Type == InteractedElementType_Input)
                return baseResult;

            return WorkspaceMouseInteractionResult(this, type);
        } else {
            RemoveFlags(WorkspaceInteractionFlags_Hovered);
        }

        return baseResult;
    }

    void WorkspaceNode::AddPins(const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            std::shared_ptr<WorkspaceInputPin> inputPin = std::make_shared<WorkspaceInputPin>(inputs[i], this, inputs[i].Description);
            inputPin->SetParent(this);

            m_InputPins.push_back(inputPin);
            m_Children.push_back(inputPin);
        }

        for (size_t i = 0; i < outputs.size(); ++i) {
            std::shared_ptr<WorkspaceOutputPin> outputPin = std::make_shared<WorkspaceOutputPin>(outputs[i], this, outputs[i].Description);
            outputPin->SetParent(this);

            m_OutputPins.push_back(outputPin);
            m_Children.push_back(outputPin);
        }
    }

    void WorkspaceNode::AddWorkspaceInputs(const std::vector<std::shared_ptr<WorkspaceOutputPin>>& outputPins) {
        for (std::size_t i = 0; i < outputPins.size(); ++i) {
            const std::shared_ptr<WorkspaceOutputPin>& outputPin = outputPins[i];

            std::shared_ptr<WorkspaceInput>            input = nullptr;

            switch (outputPin->Output.Type) {
                case WorkspaceIOType_Bool: input = std::make_shared<WorkspaceInputBool>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                case WorkspaceIOType_Float: input = std::make_shared<WorkspaceInputFloat>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                case WorkspaceIOType_Vec3: input = std::make_shared<WorkspaceInputVector3>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                case WorkspaceIOType_Vec4: input = std::make_shared<WorkspaceInputVector4>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                case WorkspaceIOType_Mat4: input = std::make_shared<WorkspaceInputMatrix>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                case WorkspaceIOType_Quat: input = std::make_shared<WorkspaceInputQuat>(outputPin, m_Id, i, m_Style.InputWidth, m_Style.LineHeight); break;

                default: break;
            }

            if (input != nullptr) {
                input->SetParent(this);
                m_Children.push_back(input);
                m_Inputs.push_back(input);
            }
        }
    }

    void WorkspaceNode::RecalculateSizes() {
        // Recalculate title size with margin
        m_TitleSize = ImGui::CalcTextSize(m_Title.c_str());
        m_TitleSize.x += m_Style.TitleMargin.x + m_Style.TitleMargin.z;
        m_TitleSize.y += m_Style.TitleMargin.y + m_Style.TitleMargin.w;

        float inputPinAreaHeight = 0;
        for (const auto& inputPin : m_InputPins) {
            inputPinAreaHeight += std::max(m_Style.LineHeight, inputPin->GetSize().y);
        }

        float outputPinAreaHeight = 0;
        for (const auto& outputPin : m_OutputPins) {
            outputPinAreaHeight += std::max(m_Style.LineHeight, outputPin->GetSize().y);
        }

        ImVec2 contentSize = RecalculateContentSize();

        m_BodySize.x = contentSize.x + m_Style.ContentMargin.x + m_Style.ContentMargin.z;
        m_BodySize.y = std::max(contentSize.y + m_Style.ContentMargin.y + m_Style.ContentMargin.w, std::max(inputPinAreaHeight, outputPinAreaHeight));

        // Title could be wider than content with inputs
        m_BodySize.x = std::max(m_BodySize.x, m_TitleSize.x);

        m_Size.x = m_BodySize.x;
        m_Size.y = m_TitleSize.y + m_BodySize.y;
    }

    ImVec2 WorkspaceNode::RecalculateContentSize() const {
        ImVec2 contentSize;
        for (const auto& input : m_Inputs) {
            const ImVec2& inputSize = input->GetSize();

            contentSize.x = std::max(contentSize.x, inputSize.x);
            contentSize.y += inputSize.y;
        }

        return contentSize;
    }

    void WorkspaceNode::RecalculatePinPositions() {
        float inputPinHeightSum = 0;
        for (const auto& inputPin : m_InputPins)
            inputPinHeightSum += inputPin->GetSize().y;

        ImVec2 position(0, m_TitleSize.y);

        // Set positions for input pins
        for (auto& inputPin : m_InputPins) {
            float inputHeight = inputPin->GetSize().y;
            float halfShift   = m_BodySize.y / inputPinHeightSum * inputHeight / 2;

            position.y += halfShift;
            inputPin->SetPosition(position);
            position.y += halfShift;
        }

        position.x = m_BodySize.x;
        position.y = m_TitleSize.y;

        float outputPinHeightSum = 0;
        for (const auto& outputPin : m_OutputPins)
            outputPinHeightSum += outputPin->GetSize().y;

        // Set positions for output pins
        for (auto& outputPin : m_OutputPins) {
            float inputHeight = outputPin->GetSize().y;
            float halfShift   = m_BodySize.y / outputPinHeightSum * inputHeight / 2;

            position.y += halfShift;
            outputPin->SetPosition(position);
            position.y += halfShift;
        }
    }

    void WorkspaceNode::RecalculateInputPositions() {
        ImVec2 contentAreaSize(m_BodySize.x - m_Style.ContentMargin.x - m_Style.ContentMargin.z, m_BodySize.y - m_Style.ContentMargin.y - m_Style.ContentMargin.w);
        ImVec2 nextInputPosition(0, m_Style.ContentMargin.y + m_TitleSize.y);

        float  inputHeightSum = 0;
        for (const auto& input : m_Inputs)
            inputHeightSum += input->GetSize().y;

        for (auto&& input : m_Inputs) {
            const ImVec2& inputSize = input->GetSize();

            nextInputPosition.x = (contentAreaSize.x - inputSize.x) / 2 + m_Style.ContentMargin.x;
            input->SetPosition(nextInputPosition);

            float shift = contentAreaSize.y / inputHeightSum * inputSize.y;
            shift       = std::max(shift, m_Style.LineHeight);
            nextInputPosition.y += shift;
        }
    }

    void WorkspaceNode::RecalculateHintPosition() {
        ImVec2 position(m_Size.x - m_Hint->GetButtonSize().x - 4, 3);
        m_Hint->SetPosition(position);
    }

    WorkspaceMouseInteractionResult WorkspaceNode::GetGeneralMouseInteraction(const WorkspaceMouseInteraction& interaction) {
        ImVec2 barMax(GetSize().x, m_TitleSize.y);

        if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, 0), barMax))
            return WorkspaceMouseInteractionResult(this, InteractedElementType_NodeBar, m_AdditionalOptions);
        if (IsPositionInsideRectanle(interaction.mousePosition, ImVec2(0, barMax.y), GetSize()))
            return WorkspaceMouseInteractionResult(this, InteractedElementType_NodeBody);

        return WorkspaceMouseInteractionResult();
    }

    void WorkspaceNode::RecalculateContentMargin() {
        float maxInputWidth = 0;

        for (auto&& input : m_InputPins) {
            const ImVec2& size = input->GetSize();
            if (size.x > maxInputWidth)
                maxInputWidth = size.x;
        }

        float maxOutputWidth = 0;
        for (auto&& output : m_OutputPins) {
            const ImVec2& size = output->GetSize();
            if (size.x > maxOutputWidth)
                maxOutputWidth = size.x;
        }

        m_Style.ContentMargin.x = std::max(m_Style.PinPadding, maxInputWidth);
        m_Style.ContentMargin.z = std::max(m_Style.PinPadding, maxOutputWidth);
    }
} // namespace AVC3T
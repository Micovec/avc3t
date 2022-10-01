#pragma once

#include "WorkspaceNode.h"
#include "imgui.h"

namespace AVC3T {
    class WorkspaceScalableNode;

    struct WorkspaceScalableTriangle : public WorkspaceElement {
        WorkspaceScalableTriangle(WorkspaceScalableNode* parent, const ImVec2& minSize, const ImVec2& maxSize, const ImVec2& position = ImVec2(0, 0)) :
            WorkspaceElement(), m_MinSize(minSize), m_MaxSize(maxSize), m_OutsideSizeRecord(0, 0), m_TriangleColor(s_DefaultColor) {
            m_Position = position;

            m_TrianglePositions[0].x = 0;
            m_TrianglePositions[0].y = 0;
            m_TrianglePositions[1].x = m_TrianglePositions[0].x - s_TriangleSize;
            m_TrianglePositions[1].y = m_TrianglePositions[0].y;
            m_TrianglePositions[2].x = m_TrianglePositions[0].x;
            m_TrianglePositions[2].y = m_TrianglePositions[0].y - s_TriangleSize;
        }

        WorkspaceScalableTriangle(const WorkspaceScalableTriangle& other) :
            WorkspaceElement(), m_MinSize(other.m_MinSize), m_MaxSize(other.m_MaxSize), m_OutsideSizeRecord(0, 0), m_TriangleColor(other.m_TriangleColor) {
            m_Position = other.m_Position;

            m_TrianglePositions[0] = other.m_TrianglePositions[0];
            m_TrianglePositions[1] = other.m_TrianglePositions[1];
            m_TrianglePositions[2] = other.m_TrianglePositions[2];
        }

        virtual void Render(WorkspaceRenderContext& context) override {
            ImVec2 absolutePosition = GetAbsolutePosition(context);
            ImVec2 rightCorner(context.Origin.x + absolutePosition.x, context.Origin.y + absolutePosition.y);
            ImVec2 leftCorner(rightCorner.x - s_TriangleSize, rightCorner.y);
            ImVec2 topCorner(rightCorner.x, rightCorner.y - s_TriangleSize);

            context.DrawList->AddTriangleFilled(rightCorner, leftCorner, topCorner, m_TriangleColor);
        }

        virtual void SetPosition(const ImVec2& position) override {
            ImVec2 delta(position.x - m_Position.x, m_Position.y - position.y);
            WorkspaceElement::SetPosition(position);

            if (m_Position.x < m_MinSize.x) {
                m_OutsideSizeRecord.x += m_Position.x - m_MinSize.x;
                m_Position.x = m_MinSize.x;
            } else if (m_Position.x > m_MaxSize.x) {
                m_OutsideSizeRecord.x += m_Position.x - m_MaxSize.x;
                m_Position.x = m_MaxSize.x;
            } else if (m_OutsideSizeRecord.x) {
                bool wasNegative = m_OutsideSizeRecord.x < 0;
                m_OutsideSizeRecord.x += delta.x;

                if (wasNegative && m_OutsideSizeRecord.x > 0) {
                    m_Position.x          = m_MinSize.x - m_OutsideSizeRecord.x;
                    m_OutsideSizeRecord.x = 0;
                } else {
                    m_Position.x = m_MinSize.x;
                }
            }

            if (m_Position.y < m_MinSize.y) {
                m_OutsideSizeRecord.y += m_Position.y - m_MinSize.y;
                m_Position.y = m_MinSize.y;
            } else if (m_Position.y > m_MaxSize.y) {
                m_OutsideSizeRecord.y += m_Position.y - m_MaxSize.y;
                m_Position.y = m_MaxSize.y;
            } else if (m_OutsideSizeRecord.y) {
                bool wasNegative = m_OutsideSizeRecord.y < 0;
                m_OutsideSizeRecord.y -= delta.y;

                if (wasNegative && m_OutsideSizeRecord.y > 0) {
                    m_Position.y += delta.y;
                    m_OutsideSizeRecord.y = 0;
                } else {
                    m_Position.y = m_MinSize.y;
                }
            }
        }

        virtual WorkspaceMouseInteractionResult MousePressed(const WorkspaceMouseInteraction& interaction) override {
            if (interaction.mouseButton == MouseButton::Left &&
                IsPositionInsideTriangle(interaction.mousePosition, m_TrianglePositions[0], m_TrianglePositions[1], m_TrianglePositions[2]))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Element);

            return WorkspaceElement::MousePressed(interaction);
        }

        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override {
            if (IsPositionInsideTriangle(interaction.mousePosition, m_TrianglePositions[0], m_TrianglePositions[1], m_TrianglePositions[2]))
                return WorkspaceMouseInteractionResult(this, InteractedElementType_Element);

            return WorkspaceElement::MousePositionUpdate(interaction);
        }

      protected:
        constexpr static float   s_TriangleSize = 10;
        constexpr static ImColor s_DefaultColor = {0.5f, 0.5f, 0.5f, 1.f};

        ImVec2                   m_MinSize, m_MaxSize, m_OutsideSizeRecord;

        ImColor                  m_TriangleColor;
        ImVec2                   m_TrianglePositions[3];
    };

    class WorkspaceScalableNode : public WorkspaceNode {
      public:
        WorkspaceScalableNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                              const WorkspaceNodeStyle& style, const std::string_view& hint = std::string_view(),
                              const std::vector<WorkspaceMouseInteractionOption>& additionalOptions = {});
        WorkspaceScalableNode(const std::string& title, const std::vector<WorkspaceNodeInput>& inputs, const std::vector<WorkspaceNodeOutput>& outputs,
                              const WorkspaceNodeStyle& style, const ImVec2& bodySize, const std::string_view& hint = std::string_view(),
                              const std::vector<WorkspaceMouseInteractionOption>& additionalOptions = {});
        WorkspaceScalableNode(const WorkspaceScalableNode& other);

        virtual ~WorkspaceScalableNode() {}

        void SetSize(const ImVec2& size);

      protected:
        virtual ImVec2 RecalculateContentSize() const override;

      protected:
        std::shared_ptr<WorkspaceScalableTriangle> m_Triangle;

      private:
        constexpr static float s_TriangleMargin = 4;
    };
} // namespace AVC3T
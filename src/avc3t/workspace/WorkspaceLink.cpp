#include "WorkspaceLink.h"

namespace AVC3T {
    WorkspaceLink::WorkspaceLink(WorkspaceInputPin& input, WorkspaceOutputPin& output) : InputPin(input), OutputPin(output), m_Points(), m_OriginShift() {}

    void WorkspaceLink::Render(WorkspaceRenderContext& context) {
        m_Points.clear();
        m_OriginShift = context.Origin;
        CalculateLines(context);

        for (std::size_t i = 1; i < m_Points.size(); ++i)
            context.DrawList->AddLine(m_Points[i - 1], m_Points[i], IM_COL32(255, 255, 255, 255), s_LineWidth);
    }

    WorkspaceMouseInteractionResult WorkspaceLink::MouseClicked(const WorkspaceMouseInteraction& interaction) {
        if (!interaction.Handled && PositionAtLine(interaction.mousePosition))
            return WorkspaceMouseInteractionResult(this, InteractedElementType_Link);

        return WorkspaceMouseInteractionResult();
    }

    WorkspaceMouseInteractionResult WorkspaceLink::MousePositionUpdate(const WorkspaceMouseInteraction& interaction) {
        if (!interaction.Handled && PositionAtLine(interaction.mousePosition))
            return WorkspaceMouseInteractionResult(this, InteractedElementType_Link);

        return WorkspaceMouseInteractionResult();
    }

    bool WorkspaceLink::PositionAtLine(const ImVec2& position) {
        const ImVec2 actualPosition(position.x + m_OriginShift.x, position.y + m_OriginShift.y);

        for (std::size_t i = 1; i < m_Points.size(); ++i) {
            const ImVec2& p0 = m_Points[i - 1];
            const ImVec2& p1 = m_Points[i];

            ImVec2        direction(p0.x - p1.x, p0.y - p1.y);
            float         c = -(direction.x * p0.x + direction.y + p0.y);

            float         distanceFromLine   = abs(direction.x * actualPosition.x + direction.y + actualPosition.y + c) / sqrt(pow(direction.x, 2) + pow(direction.y, 2));
            float         distanceFromP0Pow2 = pow(actualPosition.x - p0.x, 2) + pow(actualPosition.y - p0.y, 2);
            float         distanceFromP1Pow2 = pow(actualPosition.x - p1.x, 2) + pow(actualPosition.y - p1.y, 2);

            float         distanceThresholdPow2 = s_PosDistanceThreshold * s_PosDistanceThreshold;

            if (distanceFromLine <= s_PosDistanceThreshold && distanceFromP0Pow2 <= distanceThresholdPow2 && distanceFromP1Pow2 <= distanceThresholdPow2)
                return true;
        }

        return false;
    }

    void WorkspaceLink::CalculateLines(WorkspaceRenderContext& context) {
        const ImVec2    outputPinPosition = OutputPin.GetAbsolutePosition();
        const ImVec2    inputPinPosition  = InputPin.GetAbsolutePosition();

        const ImVec2    p1(context.Origin.x + outputPinPosition.x, context.Origin.y + outputPinPosition.y);
        const ImVec2    p4(context.Origin.x + inputPinPosition.x, context.Origin.y + inputPinPosition.y);

        const ImVec2    direction   = ImVec2(p1.x - p4.x, p1.y - p4.y);
        const float     bezierShift = powf(direction.x * direction.x + direction.y * direction.y, 0.42f);

        const ImVec2    p2(p1.x + bezierShift, p1.y);
        const ImVec2    p3(p4.x - bezierShift, p4.y);

        constexpr float step = 1.0f / s_SegmentCount;

        for (int segment = 0; segment <= s_SegmentCount; ++segment) {
            float t = segment * step;

            float u  = 1.0f - t;
            float w1 = u * u * u;
            float w2 = 3 * u * u * t;
            float w3 = 3 * u * t * t;
            float w4 = t * t * t;

            m_Points.emplace_back(ImVec2(w1 * p1.x + w2 * p2.x + w3 * p3.x + w4 * p4.x, w1 * p1.y + w2 * p2.y + w3 * p3.y + w4 * p4.y));
        }
    }
} // namespace AVC3T
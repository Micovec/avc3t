#pragma once

#include <vector>

#include "WorkspaceElement.h"
#include "WorkspacePin.h"

namespace AVC3T {
    struct WorkspaceLink : public WorkspaceElement {
        WorkspaceLink(WorkspaceInputPin& input, WorkspaceOutputPin& output);

        void                                    Render(WorkspaceRenderContext& context) override;
        virtual WorkspaceMouseInteractionResult MouseClicked(const WorkspaceMouseInteraction& interaction) override;
        virtual WorkspaceMouseInteractionResult MousePositionUpdate(const WorkspaceMouseInteraction& interaction) override;

        WorkspaceInputPin&                      InputPin;
        WorkspaceOutputPin&                     OutputPin;

      private:
        void                         CalculateLines(WorkspaceRenderContext& context);
        bool                         PositionAtLine(const ImVec2& position);

        static constexpr int         s_SegmentCount         = 20;
        static constexpr std::size_t s_LineWidth            = 2;
        static constexpr float       s_PosDistanceThreshold = 5;

        std::vector<ImVec2>          m_Points;
        ImVec2                       m_OriginShift;
    };
}
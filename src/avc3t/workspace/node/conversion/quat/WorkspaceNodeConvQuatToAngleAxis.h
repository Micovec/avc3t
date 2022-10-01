#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvQuatToAngleAxis : public WorkspaceNode {
      public:
        WorkspaceNodeConvQuatToAngleAxis();
        WorkspaceNodeConvQuatToAngleAxis(const WorkspaceNodeConvQuatToAngleAxis& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvQuatToAngleAxis)

      private:
        float     m_OutputValueAngle;
        glm::vec3 m_OutputValueAxis;
    };
}
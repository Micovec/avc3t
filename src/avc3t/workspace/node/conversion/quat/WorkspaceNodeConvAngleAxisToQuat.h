#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvAngleAxisToQuat : public WorkspaceNode {
      public:
        WorkspaceNodeConvAngleAxisToQuat();
        WorkspaceNodeConvAngleAxisToQuat(const WorkspaceNodeConvAngleAxisToQuat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvAngleAxisToQuat)

      private:
        glm::quat m_OutputValue;
    };
}
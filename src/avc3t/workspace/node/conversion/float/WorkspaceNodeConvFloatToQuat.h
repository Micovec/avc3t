#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvFloatToQuat : public WorkspaceNode {
      public:
        WorkspaceNodeConvFloatToQuat();
        WorkspaceNodeConvFloatToQuat(const WorkspaceNodeConvFloatToQuat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvFloatToQuat)

      private:
        glm::quat m_OutputValue;
    };
}
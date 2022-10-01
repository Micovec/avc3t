#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvMat4ToQuat : public WorkspaceNode {
      public:
        WorkspaceNodeConvMat4ToQuat();
        WorkspaceNodeConvMat4ToQuat(const WorkspaceNodeConvMat4ToQuat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvMat4ToQuat)

      private:
        glm::quat m_OutputValue;
    };
}
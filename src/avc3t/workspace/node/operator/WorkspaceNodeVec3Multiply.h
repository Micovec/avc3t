#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Multiply : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Multiply();
        WorkspaceNodeVec3Multiply(const WorkspaceNodeVec3Multiply& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Multiply)

      private:
        glm::vec3 m_OutputValue;
    };
}
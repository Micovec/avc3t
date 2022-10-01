#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Normalize : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Normalize();
        WorkspaceNodeVec3Normalize(const WorkspaceNodeVec3Normalize& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Normalize)

      private:
        glm::vec3 m_OutputValue;
    };
}
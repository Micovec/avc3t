#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Mix : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Mix();
        WorkspaceNodeVec3Mix(const WorkspaceNodeVec3Mix& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Mix)

      private:
        glm::vec3 m_OutputValue;
    };
}
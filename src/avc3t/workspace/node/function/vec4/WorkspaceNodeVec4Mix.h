#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Mix : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Mix();
        WorkspaceNodeVec4Mix(const WorkspaceNodeVec4Mix& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Mix)

      private:
        glm::vec4 m_OutputValue;
    };
}
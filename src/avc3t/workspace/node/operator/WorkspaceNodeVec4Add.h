#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Add : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Add();
        WorkspaceNodeVec4Add(const WorkspaceNodeVec4Add& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Add)

      private:
        glm::vec4 m_OutputValue;
    };
}
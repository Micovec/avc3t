#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Dot : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Dot();
        WorkspaceNodeVec4Dot(const WorkspaceNodeVec4Dot& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Dot)

      private:
        float m_OutputValue;
    };
}
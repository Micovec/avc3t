#pragma once

#include "../../WorkspaceNode.h"
#include <algorithm>

namespace AVC3T {
    class WorkspaceNodeClamp : public WorkspaceNode {
      public:
        WorkspaceNodeClamp();
        WorkspaceNodeClamp(const WorkspaceNodeClamp& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeClamp)

      private:
        float m_OutputValue;
    };
}
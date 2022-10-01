#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeSign : public WorkspaceNode {
      public:
        WorkspaceNodeSign();
        WorkspaceNodeSign(const WorkspaceNodeSign& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeSign)

      private:
        float m_OutputValue;
    };
}
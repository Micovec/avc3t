#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeBoolXor : public WorkspaceNode {
      public:
        WorkspaceNodeBoolXor();
        WorkspaceNodeBoolXor(const WorkspaceNodeBoolXor& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeBoolXor)

      private:
        bool m_OutputValue;
    };
}
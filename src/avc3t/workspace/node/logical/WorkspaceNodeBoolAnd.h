#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeBoolAnd : public WorkspaceNode {
      public:
        WorkspaceNodeBoolAnd();
        WorkspaceNodeBoolAnd(const WorkspaceNodeBoolAnd& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeBoolAnd)

      private:
        bool m_OutputValue;
    };
}
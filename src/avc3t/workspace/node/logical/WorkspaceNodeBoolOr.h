#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeBoolOr : public WorkspaceNode {
      public:
        WorkspaceNodeBoolOr();
        WorkspaceNodeBoolOr(const WorkspaceNodeBoolOr& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeBoolOr)

      private:
        bool m_OutputValue;
    };
}
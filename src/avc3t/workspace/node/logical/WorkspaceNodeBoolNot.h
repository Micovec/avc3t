#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeBoolNot : public WorkspaceNode {
      public:
        WorkspaceNodeBoolNot();
        WorkspaceNodeBoolNot(const WorkspaceNodeBoolNot& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeBoolNot)

      private:
        bool m_OutputValue;
    };
}
#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeBoolValue : public WorkspaceNode {
      public:
        WorkspaceNodeBoolValue();
        WorkspaceNodeBoolValue(const WorkspaceNodeBoolValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeBoolValue)

      private:
        bool m_OutputValue;
    };
}
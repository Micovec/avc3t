#pragma once

#include "WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTime : public WorkspaceNode {
      public:
        WorkspaceNodeTime();
        WorkspaceNodeTime(const WorkspaceNodeTime& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTime)

      private:
        float m_Delta;
        float m_SystemTime;
    };
}
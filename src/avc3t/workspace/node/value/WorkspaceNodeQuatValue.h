#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatValue : public WorkspaceNode {
      public:
        WorkspaceNodeQuatValue();
        WorkspaceNodeQuatValue(const WorkspaceNodeQuatValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatValue)

      private:
        glm::quat m_Value;
    };
}
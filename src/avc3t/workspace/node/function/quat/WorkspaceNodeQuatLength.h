#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatLength : public WorkspaceNode {
      public:
        WorkspaceNodeQuatLength();
        WorkspaceNodeQuatLength(const WorkspaceNodeQuatLength& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatLength)

      private:
        float m_OutputValue;
    };
}
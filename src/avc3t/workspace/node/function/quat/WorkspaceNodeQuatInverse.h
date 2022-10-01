#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatInverse : public WorkspaceNode {
      public:
        WorkspaceNodeQuatInverse();
        WorkspaceNodeQuatInverse(const WorkspaceNodeQuatInverse& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatInverse)

      private:
        glm::quat m_OutputValue;
    };
}
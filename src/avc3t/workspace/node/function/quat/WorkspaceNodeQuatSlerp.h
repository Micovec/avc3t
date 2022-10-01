#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatSlerp : public WorkspaceNode {
      public:
        WorkspaceNodeQuatSlerp();
        WorkspaceNodeQuatSlerp(const WorkspaceNodeQuatSlerp& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatSlerp)

      private:
        glm::quat m_OutputValue;
    };
}
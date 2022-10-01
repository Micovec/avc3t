#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatLerp : public WorkspaceNode {
      public:
        WorkspaceNodeQuatLerp();
        WorkspaceNodeQuatLerp(const WorkspaceNodeQuatLerp& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatLerp)

      private:
        glm::quat m_OutputValue;
    };
}
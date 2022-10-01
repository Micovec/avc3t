#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatNormalize : public WorkspaceNode {
      public:
        WorkspaceNodeQuatNormalize();
        WorkspaceNodeQuatNormalize(const WorkspaceNodeQuatNormalize& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatNormalize)

      private:
        glm::quat m_OutputValue;
    };
}
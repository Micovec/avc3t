#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatConjugate : public WorkspaceNode {
      public:
        WorkspaceNodeQuatConjugate();
        WorkspaceNodeQuatConjugate(const WorkspaceNodeQuatConjugate& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatConjugate)

      private:
        glm::quat m_OutputValue;
    };
}
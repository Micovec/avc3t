#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeQuatMult : public WorkspaceNode {
      public:
        WorkspaceNodeQuatMult();
        WorkspaceNodeQuatMult(const WorkspaceNodeQuatMult& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeQuatMult)

      private:
        glm::quat m_OutputValue;
    };
}
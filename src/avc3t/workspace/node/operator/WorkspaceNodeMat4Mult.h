#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Mult : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Mult();
        WorkspaceNodeMat4Mult(const WorkspaceNodeMat4Mult& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Mult)

      private:
        glm::mat4 m_Matrix;
    };
}
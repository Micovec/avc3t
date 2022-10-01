#pragma once

#include <glm/glm.hpp>

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeMat4Value : public WorkspaceNode {
      public:
        WorkspaceNodeMat4Value();
        WorkspaceNodeMat4Value(const WorkspaceNodeMat4Value& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeMat4Value)

      private:
        glm::mat4 m_Matrix;
    };
}
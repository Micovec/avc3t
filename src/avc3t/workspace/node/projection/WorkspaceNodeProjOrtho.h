#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeProjOrtho : public WorkspaceNode {
      public:
        WorkspaceNodeProjOrtho();
        WorkspaceNodeProjOrtho(const WorkspaceNodeProjOrtho& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeProjOrtho)

      private:
        glm::mat4 m_Matrix;
    };
}
#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeProjFrustum : public WorkspaceNode {
      public:
        WorkspaceNodeProjFrustum();
        WorkspaceNodeProjFrustum(const WorkspaceNodeProjFrustum& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeProjFrustum)

      private:
        glm::mat4 m_Matrix;
    };
}
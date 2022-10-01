#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeProjPerspective : public WorkspaceNode {
      public:
        WorkspaceNodeProjPerspective();
        WorkspaceNodeProjPerspective(const WorkspaceNodeProjPerspective& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeProjPerspective)

      private:
        glm::mat4 m_Matrix;
    };
}
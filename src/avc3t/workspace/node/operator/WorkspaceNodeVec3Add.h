#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec3Add : public WorkspaceNode {
      public:
        WorkspaceNodeVec3Add();
        WorkspaceNodeVec3Add(const WorkspaceNodeVec3Add& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec3Add)

      private:
        glm::vec3 m_OutputValue;
    };
}
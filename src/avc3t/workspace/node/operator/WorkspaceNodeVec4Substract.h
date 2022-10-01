#pragma once

#include "../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeVec4Substract : public WorkspaceNode {
      public:
        WorkspaceNodeVec4Substract();
        WorkspaceNodeVec4Substract(const WorkspaceNodeVec4Substract& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeVec4Substract)

      private:
        glm::vec4 m_OutputValue;
    };
}
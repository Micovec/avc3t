#pragma once

#include <glm/glm.hpp>

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeTransfTranslValue : public WorkspaceNode {
      public:
        WorkspaceNodeTransfTranslValue();
        WorkspaceNodeTransfTranslValue(const WorkspaceNodeTransfTranslValue& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeTransfTranslValue)

      private:
        glm::mat4 m_Matrix;
    };
}
#pragma once

#include "../../WorkspaceNode.h"

namespace AVC3T {
    class WorkspaceNodeConvMat4ToFloat : public WorkspaceNode {
      public:
        WorkspaceNodeConvMat4ToFloat();
        WorkspaceNodeConvMat4ToFloat(const WorkspaceNodeConvMat4ToFloat& other);

        void Evaluate(double ts) override;

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeConvMat4ToFloat)

      private:
        float m_OutputValue0;
        float m_OutputValue1;
        float m_OutputValue2;
        float m_OutputValue3;
        float m_OutputValue4;
        float m_OutputValue5;
        float m_OutputValue6;
        float m_OutputValue7;
        float m_OutputValue8;
        float m_OutputValue9;
        float m_OutputValue10;
        float m_OutputValue11;
        float m_OutputValue12;
        float m_OutputValue13;
        float m_OutputValue14;
        float m_OutputValue15;
    };
}
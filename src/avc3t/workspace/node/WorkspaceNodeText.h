#pragma once

#include "WorkspaceScalableNode.h"

#include "../WorkspaceTextArea.h"

namespace AVC3T {
    class WorkspaceNodeText : public WorkspaceScalableNode {
      public:
        WorkspaceNodeText(bool multiline);
        WorkspaceNodeText(const WorkspaceNodeText& other);

        void               Render(WorkspaceRenderContext& context) override;
        void               Evaluate(double ts) override;

        const std::string& GetText() const {
            return m_TextArea->GetText();
        }
        void SetText(const std::string& text) {
            m_TextArea->SetText(text);
        }

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeText)

      protected:
        void InitializeMembers(bool multiline);

      protected:
        std::shared_ptr<WorkspaceTextArea> m_TextArea;
    };
}
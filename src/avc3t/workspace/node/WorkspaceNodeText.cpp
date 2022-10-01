#include "WorkspaceNodeText.h"

namespace AVC3T {
    WorkspaceNodeText::WorkspaceNodeText(bool multiline) : WorkspaceScalableNode("Text", {}, {}, {IM_COL32(190, 35, 52, 255)}, ImVec2(110, 110)), m_TextArea(nullptr) {
        InitializeMembers(multiline);
    }

    WorkspaceNodeText::WorkspaceNodeText(const WorkspaceNodeText& other) :
        WorkspaceScalableNode(other.m_Title, {}, {}, other.m_Style, other.m_BodySize, other.m_Hint->GetHintText()) {
        InitializeMembers(other.m_TextArea->IsMultiline());
    }

    void WorkspaceNodeText::InitializeMembers(bool multiline) {
        m_TextArea = std::make_shared<WorkspaceTextArea>(ID::Generate(), multiline, true);
        m_Children.push_back(m_TextArea);

        m_Style.ContentMargin.y = m_Style.ContentMargin.w = 12;

        const ImVec2 contentTopLeft = ImVec2(m_Style.ContentMargin.x, m_Style.ContentMargin.y + m_TitleSize.y);
        m_TextArea->SetPosition(contentTopLeft);
    }

    void WorkspaceNodeText::Render(WorkspaceRenderContext& context) {
        WorkspaceScalableNode::Render(context);

        const ImVec2 size        = GetSize();
        const ImVec2 contentSize = ImVec2(size.x - m_Style.ContentMargin.x - m_Style.ContentMargin.z, size.y - m_Style.ContentMargin.y - m_Style.ContentMargin.w - m_TitleSize.y);

        m_TextArea->SetSize(contentSize);
    }

    void WorkspaceNodeText::Evaluate(double ts) {
        // Nothing to evaluate
    }
}
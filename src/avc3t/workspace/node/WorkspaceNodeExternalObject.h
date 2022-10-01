#pragma once

#include <functional>
#include <memory>

#include "../../scene/Scene.h"
#include "../WorkspaceTextArea.h"
#include "../WorkspaceButton.h"

#include "WorkspaceNode.h"
#include "WorkspaceNodeEmbeddedObject.h"

namespace AVC3T {
    class WorkspaceNodeExternalObject : public WorkspaceNode {
      public:
        WorkspaceNodeExternalObject(Scene& scene, const std::string& path = "");
        WorkspaceNodeExternalObject(const WorkspaceNodeExternalObject& other);
        ~WorkspaceNodeExternalObject() noexcept;

        void               Evaluate(double ts) override;

        virtual void       Render(WorkspaceRenderContext& context) override;

        const std::string& GetPath() const {
            return m_TextArea->GetText();
        }

        GENERATE_NODE_COPY_METHOD(WorkspaceNodeExternalObject)

      protected:
        virtual ImVec2 RecalculateContentSize() const override;

      private:
        void                                         InitializeMembers();
        void                                         ReloadObject();
        void                                         RenderErrorMessage(WorkspaceRenderContext& context);
        std::shared_ptr<WorkspaceNodeEmbeddedObject> CreateEmbeddedObject();

      private:
        static void                            ButtonCallback(void* userData);
        static InteractionOptionCallbackDemand EmbedOptionCallback(void* data);

      private:
        Scene&                             m_Scene;
        std::shared_ptr<SceneObject>       m_SceneObject;
        std::shared_ptr<WorkspaceTextArea> m_TextArea;
        std::shared_ptr<WorkspaceButton>   m_LoadButton;
        std::string                        m_ObjectFilename;
        std::string                        m_LoadErrorMessage;
        bool                               m_CanEmbed;

      private:
        static constexpr float  s_ItemSpacing = 10;
        static constexpr ImVec2 s_InputSize   = ImVec2(200, 20);
    };
}
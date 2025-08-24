#include <initializer_list>
#include <map>
#include <string>

namespace AVC3T {
    class WorkspaceNodeBinaryStore {
      public:
        WorkspaceNodeBinaryStore(WorkspaceNodeBinaryStore& other) = delete;

        static size_t             GetNodeType(const std::string& nodeName);
        static const std::string& GetNodeName(size_t nodeType);

        WorkspaceNodeBinaryStore& operator=(const WorkspaceNodeBinaryStore& other) = delete;

      private:
        WorkspaceNodeBinaryStore(std::initializer_list<std::string> initList);

        static const WorkspaceNodeBinaryStore& GetInstance();

      private:
        std::map<size_t, std::string> m_NodeTypeToName;
        std::map<std::string, size_t> m_NodeNameToType;
    };
}

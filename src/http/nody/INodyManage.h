#include <QtCore>

namespace IWebCore {

struct INody;
class INodyManage 
{
public: 
    using Function = std::function<void(const QString&)>;

private:
    INodyManage() = default;
    INodyManage(const INodyManage&) = delete;
    INodyManage& operator=(const INodyManage&) = delete;

public:
    static INodyManage* instance();
    INody* parseFile(const QString& path);
    INody* parseContent(const QString& content);

    void addContextPath(const QString& path);
    QStringList getContextPaths() const;

    void addFunction(const QString& functionName, Function functionBody);
    Function getFunction(const QString& functionName);

private:
    std::map<QString, Function> m_functionMap;
    QStringList m_contextPaths;
};

}

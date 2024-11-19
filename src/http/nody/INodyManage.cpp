#include "INodyManage.h"
#include "INody.h"
#include "INodyParser.h"

namespace IWebCore {

INodyManage *INodyManage::instance() {
    static INodyManage instance;
    return &instance;
}

INody* INodyManage::parseFile(const QString& path)
{
    QStringList list;
    QFileInfo fileInfo(path);
    if(fileInfo.exists() && fileInfo.isFile()){
        list.append(path);
    }else{
        auto dirs = INodyManage::instance()->getContextPaths();
        for(auto dir : dirs){
            QFileInfo fileInfo(dir + "/" + path);
            if(fileInfo.exists() && fileInfo.isFile()){
                list.append(fileInfo.absoluteFilePath());
            }
        }
    }

    if(list.isEmpty()){
        throw INodyException("parsed file not exist : " + path, {});
    }else if(list.size() >= 2){
        throw INodyException("parsed file matched more than one. MatchPath:" + list.join(", "), {});
    }

    return INodyParser{}.parseFile(list.first());
}

INody* INodyManage::parseContent(const QString& str)
{
    INodyParser parser;
    return parser.parseContent(str);
}

void INodyManage::addContextPath(const QString &path)
{
    m_contextPaths.append(path);
}

QStringList INodyManage::getContextPaths() const
{
    return m_contextPaths;
}

void INodyManage::addFunction(const QString &functionName, INodyManage::Function functionBody){
    m_functionMap[functionName] = functionBody;
}

INodyManage::Function INodyManage::getFunction(const QString &functionName){
    if(m_functionMap.find(functionName) == m_functionMap.end()){
        return nullptr;
    }
    return m_functionMap[functionName];
}


}

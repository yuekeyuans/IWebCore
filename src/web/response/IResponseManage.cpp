#include "IResponseManage.h"
#include "IResponseWareRaw.h"
#include "IResponseWare.h"

$PackageWebCoreBegin

void IResponseManage::registerResponseType(IResponseWare *response)
{
    m_responses.append(response);
    if(!response->getPrefixMatcher().isEmpty()){
        if(m_convertResponses.contains(response->getPrefixMatcher())){
            QString tip = QString("already contain response prefix matcher. name : ").append(response->getPrefixMatcher());
            qFatal(tip.toUtf8());
        }
        m_convertResponses[response->getPrefixMatcher()] = response;
    }
}

IResponseWare* IResponseManage::convertMatch(const QString &content)
{
    static QStringList keys = m_convertResponses.keys();
    for(const auto& key : keys){
        if(content.startsWith(key)){
            return m_convertResponses[key];
        }
    }

    return nullptr;
}

void IResponseManage::registerNodyProcesser(const QString &path, Nody *nody)
{
    m_nodyProcessor[path] = nody;
}

Nody *IResponseManage::getNodyProcessor(const QString &path)
{
    if(m_nodyProcessor.contains(path)){
        return m_nodyProcessor[path];
    }
    return nullptr;
}

$PackageWebCoreEnd

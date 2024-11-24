#include "IResponseManage.h"
#include "IResponseWare.h"
#include "IResponseTemplateRenderer.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

void IResponseManage::registerResponse(const QString& name, IResponseWare *response)
{
    assert(!m_responses.contains(name));
    m_responses[name] = response;

    if(!response->prefixMatcher().isEmpty()){
        assert(!m_convertableResponses.contains(response->prefixMatcher()));
        m_convertableResponses[response->prefixMatcher()] = response;
    }
}

bool IResponseManage::containResponse(const QString &name)
{
    const auto& keys = m_responses.keys();
    for(const auto& key : keys){
        if(key.endsWith(name)){
            return true;
        }
    }
    return false;
}

IResponseWare* IResponseManage::convertableMatch(const QString &content)
{
    static QStringList keys = m_convertableResponses.keys();
    for(const auto& key : keys){
        if(content.startsWith(key)){
            return m_convertableResponses[key];
        }
    }

    return nullptr;
}

$PackageWebCoreEnd

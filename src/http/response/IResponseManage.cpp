#include "IResponseManage.h"
#include "IResponseWare.h"
#include "IResponseTemplateRenderer.h"
#include "http/net/impl/IResponseRaw.h"

$PackageWebCoreBegin

IResponseManage::~IResponseManage()
{
    delete m_templateRenderer;
}

void IResponseManage::registerResponseType(const QString& name, IResponseWare *response)
{
    assert(!m_responses.contains(name));
    m_responses[name] = response;

    if(!response->getPrefixMatcher().isEmpty()){
        assert(!m_convertResponses.contains(response->getPrefixMatcher()));
        m_convertResponses[response->getPrefixMatcher()] = response;
    }
}

bool IResponseManage::containResponseType(const QString &name)
{
    const auto& keys = m_responses.keys();
    for(const auto& key : keys){
        if(key.endsWith(name)){
            return true;
        }
    }
    return false;
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

IResponseTemplateRenderer *IResponseManage::getTemplateRenderer()
{
    return m_templateRenderer;
}

void IResponseManage::setTemplateRenderer(IResponseTemplateRenderer *renderTemplate)
{
    m_templateRenderer = renderTemplate;
}

$PackageWebCoreEnd

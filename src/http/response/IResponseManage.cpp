#include "IResponseManage.h"
#include "IResponseRaw.h"
#include "IResponseWare.h"
#include "IResponseTemplateRenderer.h"

$PackageWebCoreBegin

IResponseManage::~IResponseManage()
{
    delete m_templateRenderer;
}

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

IResponseTemplateRenderer *IResponseManage::getTemplateRenderer()
{
    return m_templateRenderer;
}

void IResponseManage::setTemplateRenderer(IResponseTemplateRenderer *renderTemplate)
{
    m_templateRenderer = renderTemplate;
}

$PackageWebCoreEnd

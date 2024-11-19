#include "IRendererResponse.h"
#include "IResponseManage.h"
#include "http/nody/INody.h"
#include "IResponseTemplateRenderer.h"
#include "http/invalid/IHttpInternalErrorInvalid.h"

$PackageWebCoreBegin

IRendererResponse::IRendererResponse(const QString &path, QJsonObject value)
{
    IResponseTemplateRenderer* renderTemplate = IResponseManage::instance()->getTemplateRenderer();
    if(renderTemplate && renderTemplate->isPathExist(path)){
        setMime(IHttpMime::TEXT_HTML_UTF8);
        m_raw->setContent(renderTemplate->render(path, value));
    }else{
        m_raw->setContent(IHttpInternalErrorInvalid("template can not parse template:" + path));
    }
}

$PackageWebCoreEnd

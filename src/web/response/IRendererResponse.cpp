#include "IRendererResponse.h"
#include "IResponseManage.h"
#include "INody.h"
#include "IResponseRendererInterface.h"

$PackageWebCoreBegin

IRendererResponse::IRendererResponse(const QString &path, QJsonObject value)
{
    static IResponseRendererInterface* renderTemplate = IResponseManage::instance()->getRenderTemplate();
    if(renderTemplate->isPathExist(path)){
        setMime(IHttpMime::TEXT_HTML_UTF8);
        m_raw->setContent(renderTemplate->render(path, value));
    }else{
        setInvalid(IHttpStatus::INTERNAL_SERVER_ERROR_500, "template can not parse template:" + path);
    }
}

$PackageWebCoreEnd

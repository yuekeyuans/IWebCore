#include "INodyResponse.h"
#include "IResponseManage.h"
#include "Nody.h"

$PackageWebCoreBegin

INodyResponse::INodyResponse(const QString &path, QJsonValue value)
{
    auto nody = IResponseManage::instance()->getNodyProcessor(path);
    if(nody != nullptr){
        setMime(IHttpMime::TEXT_HTML_UTF8);
        QMap<QString, QJsonValue> map;
        m_raw->setContent(nody->operator ()(value, map));
    }else{
        setInvalid(IHttpStatus::INTERNAL_SERVER_ERROR_500, "template can not found:" + path);
    }
}

$PackageWebCoreEnd

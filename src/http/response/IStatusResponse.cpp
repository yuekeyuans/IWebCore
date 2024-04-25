#include "IStatusResponse.h"
#include "core/base/IConvertUtil.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

$UseAssert(IHttpAssert)

IStatusResponse::IStatusResponse(QString num)
{
    m_raw->statusCode = IHttpStatus::toStatus(num);
    if(m_raw->statusCode == IHttpStatusCode::UNKNOWN){
        $Ast->fatal("http_status_code_convert_failed");
    }
}

IStatusResponse::IStatusResponse(int code, const QString& errorMsg)
{
    m_raw->statusCode = IHttpStatus::toStatus(code);
    if(m_raw->statusCode == IHttpStatusCode::UNKNOWN){
        $Ast->fatal("http_status_code_convert_failed");
    }

    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

IStatusResponse::IStatusResponse(IHttpStatusCode status, const QString &errorMsg)
{
    m_raw->statusCode = status;

    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

QString IStatusResponse::getPrefixMatcher()
{
    return "$status:";
}

IStatusResponse operator"" _status(unsigned long long int value)
{
    return IStatusResponse(value);
}

$PackageWebCoreEnd

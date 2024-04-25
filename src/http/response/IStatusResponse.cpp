#include "IStatusResponse.h"
#include "core/base/IConvertUtil.h"
#include "http/IHttpAssert.h"

$PackageWebCoreBegin

namespace IStatusCodeResponseHelper{
    void checkStatusCode(IHttpStatusCode);
}

IStatusResponse::IStatusResponse(QString num)
{
    auto statusCode =  IHttpStatus::toStatus(num);
    if(statusCode == IHttpStatusCode::UNKNOWN){
        QString info = "the return value converted to IStatusCode is not correct\n Expression : " + num;
        qFatal(info.toUtf8());
    }
    m_raw->statusCode = statusCode;
}

IStatusResponse::IStatusResponse(int code, const QString& errorMsg)
{
    m_raw->statusCode = IHttpStatus::toStatus(code);

#ifdef _DEBUG
    if(m_raw->statusCode == IHttpStatus::UNKNOWN){
        qFatal("not corrected status code returned");
    }
#endif

    IStatusCodeResponseHelper::checkStatusCode(m_raw->statusCode);
    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

IStatusResponse::IStatusResponse(IHttpStatusCode status, const QString &errorMsg)
{
    m_raw->statusCode = status;
    IStatusCodeResponseHelper::checkStatusCode(m_raw->statusCode);
    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

QString IStatusResponse::getPrefixMatcher()
{
    return "$status:";
}

void IStatusCodeResponseHelper::checkStatusCode(IHttpStatusCode status)
{
    if(IHttpStatusCode::UNKNOWN == status){
        qFatal("the status code from your code is not correct, please check it");
    }
}

IStatusResponse operator"" _status(unsigned long long int value)
{
    return IStatusResponse(value);
}

$PackageWebCoreEnd

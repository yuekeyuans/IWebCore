#include "IStatusResponse.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

namespace IStatusCodeResponseHelper{
    void checkStatusCode(IHttpStatus);
}

IStatusResponse::IStatusResponse(QString num)
{
    auto statusCode =  IHttpStatusUtil::toStatus(num);
    if(statusCode == IHttpStatus::UNKNOWN){
        QString info = "the return value converted to IStatusCode is not correct\n Expression : " + num;
        qFatal(info.toUtf8());
    }
    m_raw->statusCode = statusCode;
}

IStatusResponse::IStatusResponse(int arg, const QString& errorMsg)
{
    m_raw->statusCode = IHttpStatusUtil::toStatus(arg);
    IStatusCodeResponseHelper::checkStatusCode(m_raw->statusCode);
    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

IStatusResponse::IStatusResponse(IHttpStatus status, const QString &errorMsg)
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

void IStatusCodeResponseHelper::checkStatusCode(IHttpStatus status)
{
    if(IHttpStatus::UNKNOWN == status){
        qFatal("the status code from your code is not correct, please check it");
    }
}

IStatusResponse operator"" _status(unsigned long long int value)
{
    return IStatusResponse(value);
}

$PackageWebCoreEnd

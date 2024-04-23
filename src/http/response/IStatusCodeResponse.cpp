#include "IStatusCodeResponse.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

namespace IStatusCodeResponseHelper{
    void checkStatusCode(IHttpStatus);
}

IStatusCodeResponse::IStatusCodeResponse(QString num)
{
    auto statusCode =  IHttpStatusUtil::toStatus(num);
    if(statusCode == IHttpStatus::UNKNOWN){
        QString info = "the return value converted to IStatusCode is not correct\n Expression : " + num;
        qFatal(info.toUtf8());
    }
    m_raw->statusCode = statusCode;
}

IStatusCodeResponse::IStatusCodeResponse(int arg)
{
    m_raw->statusCode = IHttpStatusUtil::toStatus(arg);
    IStatusCodeResponseHelper::checkStatusCode(m_raw->statusCode);
}

IStatusCodeResponse::IStatusCodeResponse(IHttpStatus status, const QString &errorMsg)
{
    m_raw->statusCode = status;
    m_raw->content.setContent(errorMsg);
//    setContent(errorMsg);
}

QString IStatusCodeResponse::getPrefixMatcher()
{
    return "$status:";
}

void IStatusCodeResponseHelper::checkStatusCode(IHttpStatus status)
{
    if(IHttpStatus::UNKNOWN == status){
        qFatal("the status code from your code is not correct, please check it");
    }
}

$PackageWebCoreEnd

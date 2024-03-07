#include "IStatusCodeResponse.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

const QString IStatusCodeResponse::m_matcherPrefix = "$status:";

namespace IStatusCodeResponseHelper{
    void checkStatusCode(IHttpStatus);
}

IStatusCodeResponse::IStatusCodeResponse()
{
}

IStatusCodeResponse::IStatusCodeResponse(int arg)
{
    raw->statusCode = IHttpStatusHelper::toStatus(arg);
    IStatusCodeResponseHelper::checkStatusCode(raw->statusCode);
}

IStatusCodeResponse::IStatusCodeResponse(IHttpStatus status, const QString &errorMsg)
{
    raw->statusCode = status;
    setContent(errorMsg);
}

void IStatusCodeResponse::setInstanceArg(void *param, const QString &)
{
    auto value = *static_cast<int*>(param);
    raw->statusCode = IHttpStatusHelper::toStatus(value);
    IStatusCodeResponseHelper::checkStatusCode(raw->statusCode);
}

void IStatusCodeResponse::setInstanceArg(QString &&value)
{
    QString num = value.midRef(m_matcherPrefix.length()).toUtf8();
    auto statusCode =  IHttpStatusHelper::toStatus(num);
    if(statusCode == IHttpStatus::UNKNOWN){
        QString info = "the return value converted to IStatusCode is not correct\n Expression : " + value;
        qFatal(info.toUtf8());
    }
    raw->statusCode = statusCode;
}

bool IStatusCodeResponse::canConvertFromString()
{
    return true;
}

bool IStatusCodeResponse::matchConvertString(const QString &data)
{
    return data.startsWith(m_matcherPrefix);
}

QSharedPointer<IResponseWare> IStatusCodeResponse::createInstance()
{
    return QSharedPointer<IStatusCodeResponse>::create();
}

QSharedPointer<IResponseWare> IStatusCodeResponse::createStatusCodeInstance()
{
    return QSharedPointer<IStatusCodeResponse>::create();
}

void IStatusCodeResponseHelper::checkStatusCode(IHttpStatus status)
{
    if(IHttpStatus::UNKNOWN == status){
        qFatal("the status code from your code is not correct, please check it");
    }
}

$PackageWebCoreEnd

#include "IStatusResponse.h"
#include "core/abort/IAbortInterface.h"
#include "http/response/content/IResponseContent.h"

$PackageWebCoreBegin

// TODO: 这个好像不应该出现，需要检查一下
class IStatusResponseAbort : public IAbortInterface<IStatusResponseAbort>
{
    $AsAbort(http_status_code_convert_failed)
protected:
    virtual QMap<int, QString> abortDescription() const final
    {
        return {
            { http_status_code_convert_failed, "number can not match any status code"}
        };
    }
};

IStatusResponse::IStatusResponse(const QString& num)
{
    m_raw->m_status = IHttpStatus(num.toInt());
}

IStatusResponse::IStatusResponse(const std::string & data)
    : IStatusResponse(QString::fromStdString(data))
{
}

IStatusResponse::IStatusResponse(int code, const QString& errorMsg)
{
    m_raw->m_status = IHttpStatus(code);
    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->setContent(new IResponseContent(errorMsg.toUtf8()));
    }
}

IStatusResponse::IStatusResponse(IHttpStatus status, const QString &errorMsg)
{
    m_raw->m_status = status;
    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->setContent(new IResponseContent(errorMsg.toUtf8()));
    }
}

std::string IStatusResponse::prefixMatcher()
{
    return "$status:";
}

IStatusResponse operator"" _status(unsigned long long int value)
{
    return IStatusResponse(value);
}

$PackageWebCoreEnd

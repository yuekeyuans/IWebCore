#include "IStatusResponse.h"
#include "core/util/IConvertUtil.h"
#include "core/abort/IAbortInterface.h"

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

IStatusResponse::IStatusResponse(QString num)
{
    m_raw->status = IHttpStatus::toStatus(num);
    if(m_raw->status == IHttpStatusCode::UNKNOWN){
        IStatusResponseAbort::aborthttp_status_code_convert_failed($ISourceLocation);
    }
}

IStatusResponse::IStatusResponse(int code, const QString& errorMsg)
{
    m_raw->status = IHttpStatus::toStatus(code);
    if(m_raw->status == IHttpStatusCode::UNKNOWN){
        IStatusResponseAbort::aborthttp_status_code_convert_failed($ISourceLocation);
    }

    if(!errorMsg.isEmpty()){
        m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
        m_raw->content.setContent(errorMsg);
    }
}

IStatusResponse::IStatusResponse(IHttpStatusCode status, const QString &errorMsg)
{
    m_raw->status = status;

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

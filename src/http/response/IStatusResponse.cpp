#include "IStatusResponse.h"
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

IStatusResponse::IStatusResponse(const QString& num)
{
    m_raw->m_status = IHttpStatusUtil::toStatus(num);
//    if(m_raw->m_status == IHttpStatus::UNKNOWN){
//        IStatusResponseAbort::aborthttp_status_code_convert_failed($ISourceLocation);
    //    }
}

IStatusResponse::IStatusResponse(const std::string & data)
    : IStatusResponse(QString::fromStdString(data))
{
}

// skip check
IStatusResponse::IStatusResponse(int code, const QString& errorMsg)
{
//    if(m_raw->m_status == IHttpStatus::UNKNOWN){
//        IStatusResponseAbort::aborthttp_status_code_convert_failed($ISourceLocation);
//    }
    m_raw->m_status = IHttpStatusUtil::toStatus(code);
    if(!errorMsg.isEmpty()){
        m_raw->setContent(errorMsg);
    }
}

IStatusResponse::IStatusResponse(IHttpStatus status, const QString &errorMsg)
{
    m_raw->m_status = status;
    if(!errorMsg.isEmpty()){
        m_raw->setContent(errorMsg);
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

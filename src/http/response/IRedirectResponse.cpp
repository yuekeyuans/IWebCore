#include "IRedirectResponse.h"
#include "core/util/ICodecUtil.h"

$PackageWebCoreBegin

IRedirectResponse::IRedirectResponse()
{
    m_raw->m_status = IHttpStatus::FOUND_302;
}

IRedirectResponse::IRedirectResponse(const char *data)
{
    m_raw->m_status = IHttpStatus::FOUND_302;
    this->m_redirectPath = data;
    updateLocationPath();
}

IRedirectResponse::IRedirectResponse(const QString &path)
{
    m_raw->m_status = IHttpStatus::FOUND_302;
    this->m_redirectPath = path;
    updateLocationPath();
}

IRedirectResponse::IRedirectResponse(const std::string &path)
    : IRedirectResponse(QString::fromStdString(path))
{
}

std::string IRedirectResponse::prefixMatcher()
{
    return "$redirect:";
}

void IRedirectResponse::updateLocationPath()
{
    if(m_redirectPath.isEmpty()){
        return;
    }
    auto path = ICodecUtil::pathEncode(m_redirectPath);
    m_raw->m_headers.insert(IHttpHeader::Location.m_view, path.toUtf8());
}

IRedirectResponse operator"" _redirect(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}

$PackageWebCoreEnd

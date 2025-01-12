#include "IFileResponse.h"
#include "core/util/ICodecUtil.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IFileUtil.h"
#include "core/config/IProfileImport.h"
#include "http/biscuits/IHttpMime.h"
#include "http/response/content/IFileResponseContent.h"

$PackageWebCoreBegin

IFileResponse::IFileResponse()
{
}

IFileResponse::IFileResponse(const char *data)
    : IFileResponse(IString(data))
{
}

IFileResponse::IFileResponse(const QString &data)
    : IFileResponse(IString(data.toUtf8()))
{
}

IFileResponse::IFileResponse(IString &&path)
{
    m_fileResponseContent = new IFileResponseContent(std::move(path));
    m_raw->setContent(m_fileResponseContent);
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IFileResponse::IFileResponse(const IString &path)
{
    m_fileResponseContent = new IFileResponseContent(path);
    m_raw->setContent(m_fileResponseContent);
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);

}

void IFileResponse::enableContentDisposition()
{
    m_fileResponseContent->setAttribute(IFileResponseContent::ContentDispoistion, IConstantUtil::True);
}

std::string IFileResponse::prefixMatcher()
{
    return "$file:";
}

IFileResponse operator"" _file(const char* str, size_t size)
{
    QByteArray array(str, static_cast<int>(size));
    QString name(array);

    IFileResponse response(name);
    return response;
}

$PackageWebCoreEnd

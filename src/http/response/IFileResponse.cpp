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

IFileResponse::IFileResponse(const QString &data)
    : IFileResponse(IString(data.toUtf8()))
{
}

IFileResponse::IFileResponse(IString &&path)
{
    m_fileRepsonse = new IFileResponseContent(std::move(path));
    m_raw->setContent(m_fileRepsonse);
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);
}

IFileResponse::IFileResponse(const IString &path)
{
    m_fileRepsonse = new IFileResponseContent(path);
    m_raw->setContent(m_fileRepsonse);
    m_raw->setMime(IHttpMime::APPLICATION_OCTET_STREAM);

}

void IFileResponse::enableContentDisposition()
{
    m_fileRepsonse->setAttribute(IFileResponseContent::ContentDispoistion, IConstantUtil::True);
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

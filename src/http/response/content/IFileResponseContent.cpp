#include "IFileResponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "core/util/IFileUtil.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(const QString &path)
    : m_path(path)
{
    // NOTE:
    assert(QFileInfo(m_path).exists());
}

int IFileResponseContent::getSize()
{
    return QFileInfo(m_path).size();
}

const char *IFileResponseContent::getType()
{
    return "file";
}

// TODO:
IStringView IFileResponseContent::getContent()
{
//    bool ok;
//    m_content = IFileUtil::readFileAsByteArray(m_path, &ok);
    return {};
}

QString IFileResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM);
}

$PackageWebCoreEnd

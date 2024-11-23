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

IStringView IFileResponseContent::getContent()
{
    QFile file(m_path);
    if(file.open(QFile::ReadOnly)){
        m_content = file.readAll();
        file.close();
    }
    return m_content;
}

QString IFileResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM);
}

$PackageWebCoreEnd

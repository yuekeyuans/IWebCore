#include "IFileResponseContent.h"
#include "http/biscuits/IHttpMime.h"
#include "core/util/IFileUtil.h"

$PackageWebCoreBegin

IFileResponseContent::IFileResponseContent(const QString &path)
    : m_path(path)
{
    assert(QFileInfo(m_path).exists());
}

int IFileResponseContent::getSize()
{
    return QFileInfo(m_path).size();
}

IStringView IFileResponseContent::getType()
{
    static const std::string type = "IFileResponseContent";
    return type;
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

IStringView IFileResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM).toStdString();
    return mime;
}

$PackageWebCoreEnd

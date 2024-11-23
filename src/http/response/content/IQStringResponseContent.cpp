#include "IQStringResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQStringResponseContent::IQStringResponseContent(QString &&val)
    : m_content(std::move(val))
{
    m_rawData = m_content.toUtf8();
}

IQStringResponseContent::IQStringResponseContent(const QString &val)
    : m_content(val)
{
    m_rawData = m_content.toUtf8();
}

int IQStringResponseContent::getSize()
{
    return m_rawData.length();
}

IStringView IQStringResponseContent::getType()
{
    static std::string type = "IQStringResponseContent";
    return type;
}

IStringView IQStringResponseContent::getContent()
{
    return IStringView(m_rawData.data(), m_rawData.length());
}

IStringView IQStringResponseContent::getSuggestedMime()
{
    static std::string mime = IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8).toStdString();
    return mime;
}


$PackageWebCoreEnd

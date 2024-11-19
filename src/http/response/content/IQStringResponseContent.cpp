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

const char *IQStringResponseContent::getType()
{
    return "QString";
}

IStringView IQStringResponseContent::getContent()
{
    return IStringView(m_rawData.data(), m_rawData.length());
}

QString IQStringResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::TEXT_PLAIN_UTF8);
}


$PackageWebCoreEnd

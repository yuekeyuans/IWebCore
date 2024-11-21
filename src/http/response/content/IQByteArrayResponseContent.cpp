#include "IQByteArrayResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQByteArrayResponseContent::IQByteArrayResponseContent(QByteArray && val)
    : m_content(std::move(val))
{
}

IQByteArrayResponseContent::IQByteArrayResponseContent(const QByteArray & val)
    : m_content(val)
{
}

int IQByteArrayResponseContent::getSize()
{
    return m_content.length();
}

const char *IQByteArrayResponseContent::getType()
{
    return "QByteArray";
}

IStringView IQByteArrayResponseContent::getContent()
{
    return IStringView(m_content.data(), m_content.length());
}

QString IQByteArrayResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM);
}

$PackageWebCoreEnd

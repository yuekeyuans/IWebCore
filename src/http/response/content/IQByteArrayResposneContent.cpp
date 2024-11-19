#include "IQByteArrayResposneContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IQByteArrayResposneContent::IQByteArrayResposneContent(QByteArray && val)
    : m_content(std::move(val))
{
}

IQByteArrayResposneContent::IQByteArrayResposneContent(const QByteArray & val)
    : m_content(val)
{
}

int IQByteArrayResposneContent::getSize()
{
    return m_content.length();
}

const char *IQByteArrayResposneContent::getType()
{
    return "QByteArray";
}

IStringView IQByteArrayResposneContent::getContent()
{
    return IStringView(m_content.data(), m_content.length());
}

QString IQByteArrayResposneContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM);
}

$PackageWebCoreEnd

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

IStringView IQByteArrayResponseContent::getType()
{
    static const std::string type =  "IQByteArrayResponseContent";
    return type;
}

IStringView IQByteArrayResponseContent::getContent()
{
    return IStringView(m_content.data(), m_content.length());
}

IStringView IQByteArrayResponseContent::getSuggestedMime()
{
    static const std::string mime = IHttpMimeUtil::toString(IHttpMime::APPLICATION_OCTET_STREAM).toStdString();
    return IStringView(mime);
}

$PackageWebCoreEnd

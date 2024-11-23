#include "IHtmlResponseContent.h"
#include "http/biscuits/IHttpMime.h"

$PackageWebCoreBegin

IHtmlResponseContent::IHtmlResponseContent(QByteArray && value)
    : m_content(std::move(value))
{
}

IHtmlResponseContent::IHtmlResponseContent(const QByteArray &value)
    : m_content(value)
{
}

// TODO: 这个转换可以后延
IHtmlResponseContent::IHtmlResponseContent(const QString &value)
    : m_content(value.toUtf8())
{
}

// TODO: optimise this mem copy
IHtmlResponseContent::IHtmlResponseContent(const std::string &value)
    : m_content(QByteArray::fromStdString(value))
{
}

int IHtmlResponseContent::getSize()
{
    return m_content.length();
}

const char *IHtmlResponseContent::getType()
{
    return "IHtmlResponseContent";
}

IStringView IHtmlResponseContent::getContent()
{
    return IStringView(m_content);
}

QString IHtmlResponseContent::getSuggestedMime()
{
    return IHttpMimeUtil::toString(IHttpMime::TEXT_HTML_UTF8);
}

$PackageWebCoreEnd

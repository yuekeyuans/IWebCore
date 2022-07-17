#include "IHtmlResponse.h"
#include "base/IMetaUtil.h"

$PackageWebCoreBegin

const QString IHtmlResponse::m_matcherPrefix{"$html:"};

IHtmlResponse::IHtmlResponse() : IResponseInterface()
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
}

IHtmlResponse::IHtmlResponse(const char *data)
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    raw->setContent(data);
}

IHtmlResponse::IHtmlResponse(const QString &data)
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    raw->setContent(data);
}

IHtmlResponse::IHtmlResponse(IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IHtmlResponse::setInstanceArg(QString &&data)
{
    raw->setMime(IHttpMime::TEXT_HTML_UTF8);
    raw->setContent(data.mid(m_matcherPrefix.length()));
}

bool IHtmlResponse::canConvertFromString()
{
    return true;
}

bool IHtmlResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

QSharedPointer<IResponseWare> IHtmlResponse::createInstance()
{
    return QSharedPointer<IResponseWare>(new IHtmlResponse);
}

IHtmlResponse operator"" _html(const char* str, size_t size)
{
    QByteArray array(str, static_cast<int>(size));
    IHtmlResponse response;
    response.setContent(array);
    return response;
}

$PackageWebCoreEnd

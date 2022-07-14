#include "IPlainTextResponse.h"
#include "IResponseWareRaw.h"

$PackageWebCoreBegin

const QString IPlainTextResponse::m_matcherPrefix {"$text:"};

IPlainTextResponse::IPlainTextResponse()
{
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const QString &value)
{
    raw->content = value.toUtf8();
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(QString &&value)
{
    raw->content = value.toUtf8();
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const char *data)
{
    raw->content = QByteArray(data);
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(IRedirectResponse &&redirectResponse)
{
    redirectTo(std::forward<IRedirectResponse &&>(redirectResponse));
}

void IPlainTextResponse::setInstanceArg(QString &&data)
{
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    if(data.startsWith(m_matcherPrefix)){
        raw->content = data.mid(m_matcherPrefix.length()).toUtf8();
    }else{
        raw->content = data.toUtf8();
    }
}

void IPlainTextResponse::setInstanceArg(void *param, const QString &)
{
    auto value = *static_cast<QString*>(param);
    setInstanceStringArg(value);
}

void IPlainTextResponse::setInstanceStringArg(const QString &arg)
{
    raw->content = arg.toUtf8();
}

IPlainTextResponse operator"" _text(const char* str, size_t size)
{
    return QString::fromLocal8Bit(str, static_cast<int>(size));
}

bool IPlainTextResponse::canConvertFromString()
{
    return true;
}

QSharedPointer<IResponseWare> IPlainTextResponse::createInstance()
{
    return QSharedPointer<IResponseWare>(new IPlainTextResponse);
}

QSharedPointer<IResponseWare> IPlainTextResponse::createIPlainTexInstance()
{
    return QSharedPointer<IResponseWare>(new IPlainTextResponse);
}

bool IPlainTextResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

$PackageWebCoreEnd

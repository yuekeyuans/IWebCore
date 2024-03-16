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
    raw->setContent(value);
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(QString &&value)
{
    raw->setContent(value);
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

IPlainTextResponse::IPlainTextResponse(const char *data)
{
    raw->setContent(QByteArray(data));
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
}

void IPlainTextResponse::setInstanceArg(QString &&data)
{
    raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    if(data.startsWith(m_matcherPrefix)){
        raw->setContent(data.mid(m_matcherPrefix.length()));
    }else{
        raw->setContent(std::forward<QString>(data));
    }
}

void IPlainTextResponse::setInstanceArg(void *param, const QString &)
{
    auto value = *static_cast<QString*>(param);
    setInstanceStringArg(value);
}

void IPlainTextResponse::setInstanceStringArg(const QString &arg)
{
    raw->setContent(arg);
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
    return QSharedPointer<IPlainTextResponse>::create();
}

QSharedPointer<IResponseWare> IPlainTextResponse::createIPlainTexInstance()
{
    return QSharedPointer<IPlainTextResponse>::create();
}

bool IPlainTextResponse::matchConvertString(const QString &str)
{
    return str.startsWith(m_matcherPrefix);
}

$PackageWebCoreEnd

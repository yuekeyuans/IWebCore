#include "IResponseWare.h"

#include "core/base/IConstantUtil.h"
#include "web/response/IResponseWareRaw.h"
#include "web/response/IRedirectResponse.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IResponseWare::IResponseWare()
    : raw(new IResponseWareRaw())
{
}

IResponseWare::IResponseWare(const IResponseWare &rhs)
    : raw(new IResponseWareRaw(*rhs.raw))
{
}

IResponseWare::IResponseWare(IResponseWare && rhs)
{
    std::swap(this->raw, rhs.raw);
}

IResponseWare &IResponseWare::operator =(const IResponseWare & rhs)
{
    delete this->raw;
    this->raw = new IResponseWareRaw(*rhs.raw);
    return *this;
}

IResponseWare &IResponseWare::operator =(IResponseWare && rhs)
{
    std::swap(this->raw, rhs.raw);
    return *this;
}

IResponseWare::~IResponseWare()
{
    delete raw;
    raw = nullptr;
}

QString &IResponseWare::operator[](const QString &header)
{
    return raw->headers[header];
}

const QString& IResponseWare::mime() const
{
    return raw->mimeString;
}

void IResponseWare::setMime(IHttpMime mime)
{
    raw->setMime(mime);
}

IHttpStatus IResponseWare::status() const
{
    return raw->statusCode;
}

void IResponseWare::setStatus(IHttpStatus statusCode)
{
    raw->statusCode = statusCode;
}

const QMap<QString, QString>& IResponseWare::headers() const
{
    return raw->headers;
}

void IResponseWare::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
        $Ast->fatal("iresponse_setHeader_with_empty_value_or_key");
        return;
    }
    raw->headers[key] = value;
}

void IResponseWare::setContent(const QByteArray& content)
{
    raw->setContent(content);
}

void IResponseWare::setContent(const QString& content)
{
    raw->setContent(content);
}

void IResponseWare::setContent(const char *content)
{
    raw->setContent(content);
}

IResponseContent &IResponseWare::getContent()
{
    return raw->content;
}


void IResponseWare::setInstanceCopy(IResponseWare *ware)
{
    std::swap(ware->raw, this->raw);
}

void IResponseWare::redirectTo(IRedirectResponse &&redirectResponse)
{
    redirectResponse.updateLocationPath();
    std::swap(this->raw, redirectResponse.raw);
}

void IResponseWare::setInvalid(IHttpStatus status, const QString &reason)
{
    raw->setInvalid(status, reason);
}

QString IResponseWare::getPrefixMatcher()
{
    return {};
}


$PackageWebCoreEnd

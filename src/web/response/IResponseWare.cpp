#include "IResponseWare.h"

#include "base/IConstantUtil.h"
#include "web/response/IResponseWareRaw.h"
#include "web/response/IRedirectResponse.h"
#include "web/IWebAssert.h"

$PackageWebCoreBegin

$UseAssert(IWebAssert)

IResponseWare::IResponseWare() : raw(new IResponseWareRaw())
{
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

QString IResponseWare::mime() const
{
    return raw->mimeString;
}

IHttpStatus IResponseWare::status() const
{
    return raw->statusCode;
}

size_t IResponseWare::contentLength() const
{
    return raw->content.length();
}

QByteArray& IResponseWare::content()
{
    return raw->content;
}

const QMap<QString, QString>& IResponseWare::headers() const
{
    return raw->headers;
}

void IResponseWare::setMime(IHttpMime mime)
{
    raw->setMime(mime);
}

void IResponseWare::setStatus(IHttpStatus statusCode)
{
    raw->statusCode = statusCode;
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

void IResponseWare::setInstanceArg(QString &&)
{
    qFatal(IConstantUtil::InheritedMethod);
}

void IResponseWare::setInstanceArg(void *arg, const QString &tag)
{
    Q_UNUSED(arg);
    Q_UNUSED(tag);
    qFatal(IConstantUtil::InheritedMethod);
}

void IResponseWare::setInstanceCopy(IResponseWare *interface)
{
    std::swap(interface->raw, this->raw);
}

void IResponseWare::redirectTo(IRedirectResponse &&redirectResponse)
{
    redirectResponse.updateLocationPath();
    std::swap(this->raw, redirectResponse.raw);
}

bool IResponseWare::canConvertFromString()
{
    return false;
}

bool IResponseWare::matchConvertString(const QString &)
{
    qFatal(IConstantUtil::InheritedMethod);
    return false;
}

void IResponseWare::updateDelayedResponse()
{
    // do nothing here;
}

QSharedPointer<IResponseWare> IResponseWare::createInstance()\
{
    qFatal(IConstantUtil::InheritedMethod);
    return nullptr;
}


$PackageWebCoreEnd

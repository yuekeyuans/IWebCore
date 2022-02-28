#include "IResponseWare.h"

#include "assertion/IAssertPreProcessor.h"
#include "base/IConstantUtil.h"
#include "common/response/IResponseWareRaw.h"
#include "common/response/IRedirectResponse.h"


$PackageWebCoreBegin


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

IHttpMime IResponseWare::mime() const
{
    return raw->mime;
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
    raw->mime = mime;
}

void IResponseWare::setStatus(IHttpStatus statusCode)
{
    raw->statusCode = statusCode;
}

void IResponseWare::setHeader(const QString &key, const QString &value)
{
    if(key.isEmpty() || value.isEmpty()){
        $AssertWarning(iresponse_setHeader_with_empty_value_or_key);
        return;
    }
    raw->headers[key] = value;
}

void IResponseWare::setContent(const QByteArray& bytes)
{
    raw->content = bytes;
}

void IResponseWare::setContent(const QString& content)
{
    raw->content = content.toUtf8();
}

void IResponseWare::setContent(const char *content)
{
    raw->content = content;
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

QSharedPointer<IResponseWare> IResponseWare::createInstance(){
    qFatal(IConstantUtil::InheritedMethod);
    return nullptr;
}

bool IResponseWare::canConvertFromString()
{
    return false;
}

bool IResponseWare::matchConvertString(const QString &){
    qFatal(IConstantUtil::InheritedMethod);
    return false;
}



$PackageWebCoreEnd

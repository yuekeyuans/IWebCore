#pragma once
#include "base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "base/IConvertUtil.h"

$PackageWebCoreBegin

class IPlainTextResponse : public IResponseInterface<IPlainTextResponse>
{
    Q_GADGET
    $AsResponse(IPlainTextResponse)
public:
    using IResponseInterface::operator[];

public:
    IPlainTextResponse();
    virtual ~IPlainTextResponse() = default;

    IPlainTextResponse(const QString& value);
    IPlainTextResponse(QString&& value);
    IPlainTextResponse(const char* data);
    IPlainTextResponse(IRedirectResponse&& redirectResponse);
    template<class T>
    IPlainTextResponse(const T& value);

    virtual void setInstanceArg(QString &&) final;
    virtual void setInstanceArg(void * param, const QString& = "") final;
    void setInstanceStringArg(const QString &arg);

    virtual bool canConvertFromString() final;
    virtual bool matchConvertString(const QString &) final;

    static QSharedPointer<IResponseWare> createIPlainTexInstance();
    virtual QSharedPointer<IResponseWare> createInstance() final;

private:
    static const QString m_matcherPrefix;
};

template<class T>
IPlainTextResponse::IPlainTextResponse(const T& value){
    raw->mime = IHttpMime::TEXT_PLAIN_UTF8;
    auto textValue = IConvertUtil::toString(value);
    raw->content = textValue.toUtf8();
}

IPlainTextResponse operator"" _text(const char* str, size_t size);

$PackageWebCoreEnd



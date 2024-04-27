#pragma once
#include "core/base/IHeaderUtil.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "core/base/IConvertUtil.h"

$PackageWebCoreBegin

class IPlainTextResponse : public IResponseInterface<IPlainTextResponse>
{
    $AsResponse(IPlainTextResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IPlainTextResponse();
    virtual ~IPlainTextResponse() = default;

    IPlainTextResponse(QString&& value);
    IPlainTextResponse(const QString& value);
    template<class T>
    IPlainTextResponse(const T& value);     // TODO: 这里要不要考虑给限制掉？

public:
    virtual QString getPrefixMatcher() final;
};

template<class T>
IPlainTextResponse::IPlainTextResponse(const T& value){
    m_raw->setMime(IHttpMime::TEXT_PLAIN_UTF8);
    auto textValue = IConvertUtil::toString(value);
    m_raw->setContent(textValue);
}

IPlainTextResponse operator"" _text(const char* str, size_t size);

$PackageWebCoreEnd



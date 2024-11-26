#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IByteArrayResponse : public IResponseInterface<IByteArrayResponse>
{
    $AsResponse(IByteArrayResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IByteArrayResponse();
    IByteArrayResponse(const char* data);
    IByteArrayResponse(QByteArray &&data);
    IByteArrayResponse(const QByteArray &data);
    IByteArrayResponse(const QString& data);
    IByteArrayResponse(std::string&&);
    IByteArrayResponse(const std::string&);

public:
    virtual std::string prefixMatcher() final;
};

IByteArrayResponse operator"" _bytes(const char* str, size_t size);

$PackageWebCoreEnd

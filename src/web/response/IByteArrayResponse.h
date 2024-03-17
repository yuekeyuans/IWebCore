#pragma once
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IByteArrayResponse : public IResponseInterface<IByteArrayResponse>
{
    $AsResponse(IByteArrayResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IByteArrayResponse();
    IByteArrayResponse(QString);
    IByteArrayResponse(const char*);
    IByteArrayResponse(QByteArray &array);  // TODO: 这个函数可能有些问题，不能够大规模使用
    IByteArrayResponse(QByteArray &&array);

    virtual QString getPrefixMatcher();
};

IByteArrayResponse operator"" _bytes(const char* str, size_t size);

$PackageWebCoreEnd

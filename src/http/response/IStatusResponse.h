#pragma once

#include <QtCore>
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IStatusResponse : public IResponseInterface<IStatusResponse>
{
    $AsResponse(IStatusResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IStatusResponse() = default;
    IStatusResponse(const QString&);
    IStatusResponse(int code, const QString& errorMsg="");
    IStatusResponse(IHttpStatus status, const QString& errorMsg="");

public:
    virtual QString prefixMatcher() final;
};

IStatusResponse operator"" _status(unsigned long long int);

$PackageWebCoreEnd

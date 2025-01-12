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
//    using IResponseInterface::operator [];

public:
    IStatusResponse() = default;
    IStatusResponse(const QString&);
    IStatusResponse(const std::string&);
    IStatusResponse(int code, const QString& errorMsg="");
    IStatusResponse(IHttpStatus status, const QString& errorMsg="");

public:
    virtual std::string prefixMatcher() final;
};

IStatusResponse operator"" _status(unsigned long long int);

$PackageWebCoreEnd

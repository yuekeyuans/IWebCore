#pragma once

#include <QtCore>
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IStatusCodeResponse : public IResponseInterface<IStatusCodeResponse>
{
    $AsResponse(IStatusCodeResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IStatusCodeResponse() = default;
    IStatusCodeResponse(QString);
    IStatusCodeResponse(int code);
    IStatusCodeResponse(IHttpStatus status, const QString& errorMsg);

public:
    virtual QString getPrefixMatcher() final;
};

$PackageWebCoreEnd

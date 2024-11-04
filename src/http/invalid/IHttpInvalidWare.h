#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpStatus.h"
//#include "http/invalid/IHttpInvalidUnit.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
class IHttpInvalidWare //: public IHttpInvalidUnit
{
public:
    IHttpInvalidWare() = default;
    IHttpInvalidWare(IHttpStatusCode, QString description);
    virtual ~IHttpInvalidWare() = default;

public:
    virtual void process(IRequest&, IResponse&);

public:
    IHttpStatusCode status{IHttpStatus::UNKNOWN};
//    QString tag;
    QString description;
};

$PackageWebCoreEnd

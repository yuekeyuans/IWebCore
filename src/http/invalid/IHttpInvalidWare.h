#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRequest;
class IResponse;
class IHttpInvalidWare
{
public:
    IHttpInvalidWare() = default;
    IHttpInvalidWare(IHttpStatusCode, QString description);
    virtual ~IHttpInvalidWare() = default;

public:
    virtual void process(IRequest&);

public:
    IHttpStatusCode status{IHttpStatus::UNKNOWN};
    QString description;
    std::function<void(IRequest&)> m_function{};
    IHttpInvalidWare* m_self{};
};

$PackageWebCoreEnd

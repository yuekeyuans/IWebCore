#pragma once

#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRequest;
class IHttpInvalidWare
{
public:
    IHttpInvalidWare(IHttpStatus, const QString& description);
    virtual ~IHttpInvalidWare() = default;

public:
    virtual void process(IRequest&);

public:
    IHttpStatus status{IHttpStatus::UNKNOWN};
    QString description;
    std::function<void(IRequest&)> m_function{nullptr};
};

$PackageWebCoreEnd

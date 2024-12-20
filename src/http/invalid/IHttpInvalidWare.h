#pragma once

#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IResponseRaw;
class IHttpInvalidWare
{
    friend class IInvalidReponseContent;
public:
    IHttpInvalidWare(IHttpStatus);
    IHttpInvalidWare(IHttpStatus, const std::string& description);
    virtual ~IHttpInvalidWare() = default;

public:
    virtual void process(const IHttpInvalidWare&, IResponseRaw&);

public:
    IHttpStatus status{IHttpStatus::UNKNOWN};
    IString description;

protected:
    std::function<void(const IHttpInvalidWare&, IResponseRaw&)> m_function{nullptr};
};

$PackageWebCoreEnd

#pragma once

#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

// TODO: 检查一下这里使用使用右值进行操作了
class IRequest;
class IResponse;
class IHttpInvalidWare
{
public:
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

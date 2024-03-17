#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "web/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRedirectResponse : public IResponseInterface<IRedirectResponse>
{
    $AsResponse(IRedirectResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IRedirectResponse();
    virtual ~IRedirectResponse() = default;

    IRedirectResponse(const char *path);
    IRedirectResponse(const QString &path);
    IRedirectResponse(IResponseWare *);

public:
    virtual QString getPrefixMatcher() final;
    void updateLocationPath();

private:
    QString redirectPath;
};

IRedirectResponse operator"" _redirect(const char* str, size_t size);

$PackageWebCoreEnd


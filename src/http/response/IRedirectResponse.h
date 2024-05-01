#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

class IRedirectResponse : public IResponseInterface<IRedirectResponse>
{
    $AsResponse(IRedirectResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IRedirectResponse();

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


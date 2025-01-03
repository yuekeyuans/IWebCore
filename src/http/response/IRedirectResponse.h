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
    IRedirectResponse(const char* data);
    IRedirectResponse(const QString &path);
    IRedirectResponse(const std::string& path);

public:
    virtual std::string prefixMatcher() final;
    void updateLocationPath();

private:
    QString m_redirectPath;
};

IRedirectResponse operator"" _redirect(const char* str, size_t size);

$PackageWebCoreEnd


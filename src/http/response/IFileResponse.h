#pragma once

#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IFileResponse : public IResponseInterface<IFileResponse>
{
    $AsResponse(IFileResponse)
public:
    using IResponseInterface::IResponseInterface;
    using IResponseInterface::operator [];

public:
    IFileResponse();
    IFileResponse(const QString& path);
    IFileResponse(IString&& path);
    IFileResponse(const IString& path);

public:
    void enableContentDisposition();

public:
    virtual std::string prefixMatcher() final;
};

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd

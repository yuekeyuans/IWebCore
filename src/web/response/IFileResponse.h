#pragma once
#include "core/base/IHeaderUtil.h"
#include "core/config/IProfileImport.h"
#include "IResponseInterface.h"
#include "IResponsePreProcessor.h"

$PackageWebCoreBegin

class IFileResponse : public IResponseInterface<IFileResponse>
{
    $AsResponse(IFileResponse)
public:
    using IResponseInterface::operator[];
    using IResponseInterface::IResponseInterface;

public:
    IFileResponse();
    IFileResponse(const char* data);
    IFileResponse(const QString& data);

public:
    virtual QString getPrefixMatcher() final;
};

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd

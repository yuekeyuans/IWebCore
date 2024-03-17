#pragma once
#include "core/base/IHeaderUtil.h"
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
    IFileResponse(const char* data);
    IFileResponse(const QString& data);

    virtual QString getPrefixMatcher() final;

private:
    bool m_enableContentDisposition {true};
};

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd

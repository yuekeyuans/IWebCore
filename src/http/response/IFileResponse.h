﻿#pragma once

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
    IFileResponse(const QString& data);

public:
    void enableContentDisposition();

public:
    virtual QString getPrefixMatcher() final;
};

IFileResponse operator"" _file(const char* str, size_t size);

$PackageWebCoreEnd

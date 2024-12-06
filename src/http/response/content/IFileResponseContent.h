#pragma once

#include "IResponseContent.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContent
{
public:
    IFileResponseContent(IString&&);
    IFileResponseContent(const IString&);

public:
    inline static const IString Type = "File";
};

$PackageWebCoreEnd

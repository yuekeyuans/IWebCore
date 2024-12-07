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
    inline static const IString ContentDispoistion = "ContentDispoistion";
    inline static const IString ContentTypeEnabled = "ContentTypeEnabled"; // find content type automaticly by suffix, default on.
};

$PackageWebCoreEnd

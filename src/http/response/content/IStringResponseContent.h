#pragma once

#include "IResponseContent.h"

$PackageWebCoreBegin

class IStringResponseContent : public IResponseContent
{
public:
    IStringResponseContent(IString&&);
    IStringResponseContent(const IString&);
};

$PackageWebCoreEnd


#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IStringResponseContent : public IResponseContentWare
{
public:
    IStringResponseContent(IString&&);
    IStringResponseContent(const IString&);
};

$PackageWebCoreEnd


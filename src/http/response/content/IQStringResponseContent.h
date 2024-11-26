#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IQStringResponseContent : public IResponseContentWare
{
public:
    IQStringResponseContent(const QString&);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};

$PackageWebCoreEnd

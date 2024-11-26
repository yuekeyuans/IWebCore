#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IJsonResponseContent : public IResponseContentWare
{
public:
    IJsonResponseContent(IJson&&);
    IJsonResponseContent(const IJson&);

    IJsonResponseContent(std::string&&);
    IJsonResponseContent(const std::string&);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};

$PackageWebCoreEnd

#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IJsonResponseContent : public IResponseContentWare, private IClassNameUnit<IJsonResponseContent>
{
public:
    IJsonResponseContent(IJson&&);
    IJsonResponseContent(const IJson&);

    IJsonResponseContent(std::string&&);
    IJsonResponseContent(const std::string&);

public:
    virtual const std::string& getType() const final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd

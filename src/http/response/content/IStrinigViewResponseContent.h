#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IStrinigViewResponseContent : public IResponseContentWare, private IClassNameUnit<IStrinigViewResponseContent>
{
public:
    IStrinigViewResponseContent(IStringView);

public:
    virtual const std::string& getType() final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd

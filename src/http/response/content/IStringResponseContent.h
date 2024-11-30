#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IStringResponseContent : public IResponseContentWare, private IClassNameUnit<IStringResponseContent>
{
public:
    IStringResponseContent(IString&&);
    IStringResponseContent(const IString&);

public:
    virtual const std::string& getType() const final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd


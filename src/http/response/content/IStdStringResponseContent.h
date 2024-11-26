#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IStdStringResponseContent : public IResponseContentWare, private IClassNameUnit<IStdStringResponseContent>
{
public:
    IStdStringResponseContent(std::string&&);
    IStdStringResponseContent(const std::string&);

public:
    virtual const std::string& getType() final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd

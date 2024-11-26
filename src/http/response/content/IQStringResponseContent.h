#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IQStringResponseContent : public IResponseContentWare, private IClassNameUnit<IQStringResponseContent>
{
public:
    IQStringResponseContent(const QString&);

public:
    virtual const std::string& getType() const final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd

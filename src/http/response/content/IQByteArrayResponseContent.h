#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IQByteArrayResponseContent : public IResponseContentWare, private IClassNameUnit<IQByteArrayResponseContent>
{
public:
    IQByteArrayResponseContent(QByteArray&&);
    IQByteArrayResponseContent(const QByteArray&);

public:
    virtual const std::string& getType() final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd

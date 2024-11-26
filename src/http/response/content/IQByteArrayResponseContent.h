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
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};

$PackageWebCoreEnd

#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IQByteArrayResponseContent : public IResponseContentWare
{
public:
    IQByteArrayResponseContent(QByteArray&&);
    IQByteArrayResponseContent(const QByteArray&);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};

$PackageWebCoreEnd

#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContentWare
{
public:
    IFileResponseContent(const QString& path);

public:
    virtual IStringView getContent() final;

private:
    QString m_path;
};

$PackageWebCoreEnd

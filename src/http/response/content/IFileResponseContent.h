#pragma once

#include "IResponseContent.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContent
{
public:
    IFileResponseContent(const QString& path);

public:
    virtual IStringView getContent() final;

private:
    QString m_path;
};

$PackageWebCoreEnd

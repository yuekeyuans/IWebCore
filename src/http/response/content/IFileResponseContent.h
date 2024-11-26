#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IFileResponseContent : public IResponseContentWare, private IClassNameUnit<IFileResponseContent>
{
public:
    IFileResponseContent(const QString& path);

public:
    virtual int getSize() final;
    virtual const std::string& getType() final;
    virtual IStringView getContent() final;
    virtual const std::string& getSuggestedMime() const final;

private:
    QString m_path;
};

$PackageWebCoreEnd

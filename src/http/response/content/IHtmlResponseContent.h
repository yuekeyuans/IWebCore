#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"

$PackageWebCoreBegin

class IHtmlResponseContent : public IResponseContentWare, private IClassNameUnit<IHtmlResponseContent>
{
public:
    IHtmlResponseContent(QByteArray&&);
    IHtmlResponseContent(const QByteArray&);
    IHtmlResponseContent(std::string&& value);
    IHtmlResponseContent(const std::string& value);
    IHtmlResponseContent(const QString&);
    IHtmlResponseContent(IStringView);

public:
    virtual const std::string& getType() final;
    virtual const std::string& getSuggestedMime() const final;
};

$PackageWebCoreEnd


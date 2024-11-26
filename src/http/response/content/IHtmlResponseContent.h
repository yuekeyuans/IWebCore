#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

// TODO: 之后考虑优化的事情
class IHtmlResponseContent : public IResponseContentWare
{
public:
    IHtmlResponseContent(QByteArray&&);
    IHtmlResponseContent(const QByteArray&);
    IHtmlResponseContent(std::string&& value);
    IHtmlResponseContent(const std::string& value);
    IHtmlResponseContent(const QString&);
    IHtmlResponseContent(IStringView);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};

$PackageWebCoreEnd


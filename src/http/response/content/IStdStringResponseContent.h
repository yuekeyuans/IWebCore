#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IStdStringResponseContent : public IResponseContentWare
{
public:
    IStdStringResponseContent(std::string&&);
    IStdStringResponseContent(const std::string&);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;

private:
    std::string m_content;
};

$PackageWebCoreEnd

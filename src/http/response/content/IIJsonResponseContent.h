#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IIJsonResponseContent : public IResponseContentWare
{
public:
    IIJsonResponseContent(IJson&&);
    IIJsonResponseContent(const IJson&);

    IIJsonResponseContent(std::string&&);
    IIJsonResponseContent(const std::string&);

public:
    virtual int getSize() final;
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

private:
    IJson m_content;
    std::string m_data;
};

$PackageWebCoreEnd

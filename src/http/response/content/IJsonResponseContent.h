#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IJsonResponseContent : public IResponseContentWare
{
public:
    IJsonResponseContent(IJson&&);
    IJsonResponseContent(const IJson&);

    IJsonResponseContent(std::string&&);
    IJsonResponseContent(const std::string&);

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

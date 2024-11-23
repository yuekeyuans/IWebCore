#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IStdStringResponseContent : public IResponseContentWare
{
public:
    IStdStringResponseContent(std::string&&);
    IStdStringResponseContent(const std::string&);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    std::string m_content;
};

$PackageWebCoreEnd

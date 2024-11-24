#pragma once

#include "IResponseContentWare.h"

class IStrinigViewResponseContent : public IResponseContentWare
{
public:
    IStrinigViewResponseContent(IStringView);

public:
    virtual int getSize() final;
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

private:
    IStringView m_content;
};


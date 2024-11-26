#pragma once

#include "IResponseContentWare.h"

class IStrinigViewResponseContent : public IResponseContentWare
{
public:
    IStrinigViewResponseContent(IStringView);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;
};


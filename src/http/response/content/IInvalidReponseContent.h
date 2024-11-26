#pragma once

#include "IResponseContentWare.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidReponseContent : public IResponseContentWare
{
public:
    IInvalidReponseContent(const IHttpInvalidWare& ware);

public:
    virtual IStringView getType() final;
    virtual IStringView getSuggestedMime() final;

public:
    IHttpInvalidWare m_ware;
};

$PackageWebCoreEnd

#pragma once

#include "IResponseContentWare.h"

$PackageWebCoreBegin

class IHttpInvalidWare;
class IInvalidReponseContent : IResponseContentWare
{
public:
    IInvalidReponseContent(IHttpInvalidWare& ware);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    IHttpInvalidWare& m_ware;
};

$PackageWebCoreEnd

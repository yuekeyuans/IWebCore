#pragma once

#include "IResponseContentWare.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidReponseContent : public IResponseContentWare
{
public:
    IInvalidReponseContent(const IHttpInvalidWare& ware);

public:
    virtual int getSize() final;
    virtual const char *getType() final;
    virtual IStringView getContent() final;
    virtual QString getSuggestedMime() final;

private:
    IHttpInvalidWare m_ware;
};

$PackageWebCoreEnd

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
    virtual IStringView getType() final;
    virtual IStringView getContent() final;
    virtual IStringView getSuggestedMime() final;

public:
    IHttpInvalidWare m_ware;
    QByteArray m_data;
};

$PackageWebCoreEnd

#pragma once

#include "IResponseContentWare.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidReponseContent : public IResponseContentWare
{
public:
    IInvalidReponseContent(const IHttpInvalidWare& ware);

public:
    IHttpInvalidWare m_ware;
};

$PackageWebCoreEnd

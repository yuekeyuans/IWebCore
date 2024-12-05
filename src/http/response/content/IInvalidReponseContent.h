#pragma once

#include "IResponseContent.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidReponseContent : public IResponseContent
{
public:
    IInvalidReponseContent(const IHttpInvalidWare& ware);
};

$PackageWebCoreEnd

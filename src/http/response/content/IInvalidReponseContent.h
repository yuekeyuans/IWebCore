#pragma once

#include "IResponseContentWare.h"
#include "core/unit/IClassNameUnit.h"
#include "http/invalid/IHttpInvalidWare.h"

$PackageWebCoreBegin

class IInvalidReponseContent : public IResponseContentWare, private IClassNameUnit<IInvalidReponseContent>
{
public:
    IInvalidReponseContent(const IHttpInvalidWare& ware);

public:
    virtual const std::string& getType() final;
    virtual const std::string& getSuggestedMime() const final;

public:
    IHttpInvalidWare m_ware;
};

$PackageWebCoreEnd

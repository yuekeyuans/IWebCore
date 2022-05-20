#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "core/unit/IJarUnit.h"

$PackageWebCoreBegin

class IReqRespRaw;

class IMultiPartJar : IRegisterMetaTypeUnit<IMultiPartJar>, public IJarUnit
{
    Q_GADGET
    $UseMetaRegistration(IMultiPartJar)
public:
    IMultiPartJar();

    virtual bool isValid() const final;

private:
    friend class IReqRespRaw;
    IReqRespRaw* raw{nullptr};
};

$PackageWebCoreEnd

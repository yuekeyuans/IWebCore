#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/IJarUnit.h"

$PackageWebCoreBegin

class IMultiPartJar : public IJarUnit, IRegisterMetaTypeUnit<IMultiPartJar>
{
    Q_GADGET
    $UseMetaRegistration(IMultiPartJar)
public:
    using IJarUnit::IJarUnit;

public:
    IMultiPartJar();
    virtual bool isValid() const final;
};

$PackageWebCoreEnd

#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/IJarUnit.h"

$PackageWebCoreBegin

// TODO: this will be supported latter, not in this version. same as ICookie
class ISessionJar : public IJarUnit, IRegisterMetaTypeUnit<ISessionJar>
{
    Q_GADGET
    $UseMetaRegistration(ISessionJar)
public:
    using IJarUnit::IJarUnit;

public:
    ISessionJar();
    virtual bool isValid() const final;
};

$PackageWebCoreEnd

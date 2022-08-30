#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IJarUnit.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

// TODO: this will be supported latter, not in this version. same as ICookie
class ISessionJar : public IJarUnit, IRegisterMetaTypeUnit<ISessionJar>
{
    Q_GADGET
    $UseMetaRegistration(ISessionJar)
public:
    ISessionJar() = default;

    virtual bool isValid() const final;
};

$PackageWebCoreEnd

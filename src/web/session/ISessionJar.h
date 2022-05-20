#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

// TODO: this will be supported latter, not in this version. same as ICookie
class ISessionJar : public IRegisterMetaTypeUnit<ISessionJar>
{
    Q_GADGET
    $UseMetaRegistration(ISessionJar)
public:
    ISessionJar() = default;
};

$PackageWebCoreEnd

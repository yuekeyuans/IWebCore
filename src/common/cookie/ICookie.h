#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

// TODO: this will be supported latter, not in this version.
class ICookie : IRegisterMetaTypeUnit<ICookie>
{
    Q_GADGET
    $UseMetaRegistration(ICookie)
public:
    ICookie() = default;
};

$PackageWebCoreEnd

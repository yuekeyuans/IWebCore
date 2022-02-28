#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "common/support/IRegisterMetaTypeUnit.h"

$PackageWebCoreBegin

// TODO: this will be supported latter, not in this version. same as ICookie
class ISession : public IRegisterMetaTypeUnit<ISession>
{
    Q_GADGET
    $UseMetaRegistration(ISession)
public:
    ISession() = default;
};

$PackageWebCoreEnd

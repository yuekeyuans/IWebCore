#pragma once

#include "core/base/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityWare.h"

$PackageWebCoreBegin

class IOrmTableInfo;

class IOrmTableWare : public IOrmEntityWare
{
public:
    IOrmTableWare() = default;

    virtual const IOrmTableInfo* getOrmEntityInfo() const override = 0;
};

$PackageWebCoreEnd

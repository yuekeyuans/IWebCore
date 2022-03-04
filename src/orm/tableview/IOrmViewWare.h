#pragma once

#include "base/IHeaderUtil.h"
#include "orm/tableview/IOrmViewInfo.h"
#include "orm/tableview/IOrmEntityWare.h"

$PackageWebCoreBegin

class IOrmViewInfo;

class IOrmViewWare : public IOrmEntityWare
{
public:
    IOrmViewWare() = default;
    virtual ~IOrmViewWare() = default;

    virtual const IOrmViewInfo* getOrmEntityInfo() const override = 0;
};

$PackageWebCoreEnd

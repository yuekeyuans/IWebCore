#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"
#include "IOrmEntityInfoWare.h"
#include "IOrmTableInfo.h"

$PackageWebCoreBegin

class IOrmTableWare : public IBeanWare{
public:
    IOrmTableWare() = default;
    virtual ~IOrmTableWare() = default;

    virtual const IOrmTableInfo& getOrmEntityInfo() const = 0;
};

$PackageWebCoreEnd

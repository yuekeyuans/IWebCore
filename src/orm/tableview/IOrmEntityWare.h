#pragma once

#include "IOrmEntityInfoWare.h"
#include "IOrmTableInfo.h"
#include "base/IHeaderUtil.h"
#include "core/bean/IBeanWare.h"

$PackageWebCoreBegin

class IOrmEntityWare : public IBeanWare{

public:
    IOrmEntityWare() = default;
    virtual ~IOrmEntityWare() = default;

    virtual const IOrmEntityInfoWare* getOrmEntityInfo() const = 0;
};

$PackageWebCoreEnd

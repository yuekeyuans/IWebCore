#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"
#include "IOrmEntityInfoWare.h"
#include "IOrmTableInfo.h"

$PackageWebCoreBegin

class IOrmEntityWare : public IBeanWare{

public:
    IOrmEntityWare() = default;
    virtual ~IOrmEntityWare() = default;

    virtual const IOrmEntityInfoWare* getOrmEntityInfo() const = 0;
};

$PackageWebCoreEnd

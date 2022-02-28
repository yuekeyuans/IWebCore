#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"

$PackageWebCoreBegin

class IOrmTableInfo;

class IOrmTableWare : public IBeanWare{
public:
    IOrmTableWare() = default;
    virtual ~IOrmTableWare() = default;

    virtual const IOrmTableInfo& getTableInfo() const = 0;
};

$PackageWebCoreEnd

#pragma once

#include "base/IHeaderUtil.h"
#include "bean/IBeanWare.h"

$PackageWebCoreBegin

class IOrmViewInfo;

class IOrmViewWare : public IBeanWare
{
public:
    IOrmViewWare() = default;
    virtual ~IOrmViewWare() = default;

    virtual const IOrmViewInfo& getViewInfo() const =0;
};

$PackageWebCoreEnd

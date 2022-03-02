#pragma once

#include "base/IHeaderUtil.h"
#include "orm/tableview/IOrmViewWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IOrmViewInterface : public IOrmViewWare
{
public:
    IOrmViewInterface() = default;
    virtual ~IOrmViewInterface() = default;

};

$PackageWebCoreEnd

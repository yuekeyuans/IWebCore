#pragma once

#include "base/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityInfoWare.h"

$PackageWebCoreBegin

class IOrmViewInfo : public IOrmEntityInfoWare
{
    $UseWare
public:
    IOrmViewInfo() = default;
    explicit IOrmViewInfo(const QMetaObject& meta);

};

$PackageWebCoreEnd

#pragma once

#include "core/base/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityInfoWare.h"

$PackageWebCoreBegin

class IOrmViewInfo : public IOrmEntityInfoWare
{
public:
    IOrmViewInfo() = default;
    explicit IOrmViewInfo(const QMetaObject& meta);

};

$PackageWebCoreEnd

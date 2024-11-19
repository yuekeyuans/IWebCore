﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "orm/tableview/IOrmEntityInfoWare.h"

$PackageWebCoreBegin

class IOrmViewInfo : public IOrmEntityInfoWare
{
public:
    IOrmViewInfo() = default;
    explicit IOrmViewInfo(const QMetaObject& meta);

};

$PackageWebCoreEnd

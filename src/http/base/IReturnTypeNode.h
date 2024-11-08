#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct IReturnTypeNode
{
public:
    QString typeName;
    QMetaType::Type typeId {QMetaType::UnknownType};    // TODO: 这个名字容易冲突
};

$PackageWebCoreEnd

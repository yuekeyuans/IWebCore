#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

struct ITypeNode
{
    QMetaType::Type typeId{QMetaType::UnknownType};
    QString typeName;
};

$PackageWebCoreEnd

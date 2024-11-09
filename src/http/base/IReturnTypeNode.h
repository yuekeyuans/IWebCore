#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

// TODO: 后续支持创建和销毁
struct IReturnTypeNode
{
    QMetaType::Type typeId {QMetaType::UnknownType};
    QString typeName;
};

$PackageWebCoreEnd

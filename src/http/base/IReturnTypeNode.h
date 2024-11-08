#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

// TODO: 后续支持创建和销毁
struct IReturnTypeNode
{
//public:
//    void* create();
//    void destroy(void*);

public:
    QString typeName;
    QMetaType::Type typeId {QMetaType::UnknownType};
};

$PackageWebCoreEnd

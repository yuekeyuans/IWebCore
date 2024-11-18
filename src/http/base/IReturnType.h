#pragma once

#include "core/util/IHeaderUtil.h"
#include <functional>

$PackageWebCoreBegin

class IRequest;
struct IReturnType
{
public:
    IReturnType() = default;
    void* create() const;
    void destroy(void*ptr) const;
    void resolveValue(IRequest& request, void* ptr) const;

public:
    QMetaType::Type typeId{QMetaType::UnknownType};
    QString typeName;
};

$PackageWebCoreEnd

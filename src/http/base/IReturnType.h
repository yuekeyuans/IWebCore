#pragma once

#include "core/util/IHeaderUtil.h"
#include <functional>

$PackageWebCoreBegin

class IRequestImpl;
struct IReturnType
{
public:
    void* create() const;
    void destroy(void*ptr) const;

public:
    QMetaType::Type m_typeId{QMetaType::UnknownType};
    std::string m_typeName;
    std::function<void(IRequestImpl&, void*)> m_resolveFunction;
};

$PackageWebCoreEnd

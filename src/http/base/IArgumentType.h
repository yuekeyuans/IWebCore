#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
struct IArgumentType
{
public:
    QMetaType::Type m_typeId{QMetaType::UnknownType};
    IString m_typeName;
    IString m_name;

public:
    std::function<void*(IRequest&)> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
};

$PackageWebCoreEnd

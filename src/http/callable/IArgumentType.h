#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
struct IArgumentType
{
public:
    enum Position{
        Auto, Path, Query, Header, Cookie, Session, Body, Form, Json,
    };

public:
    QMetaType::Type m_typeId{QMetaType::UnknownType};
    IString m_typeName;
    IString m_name;
    Position m_position{Auto};
    bool m_optional{false};

public:
    std::function<void*(IRequest&)> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
};

$PackageWebCoreEnd

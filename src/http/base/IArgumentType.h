#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
struct IArgumentType
{
    enum Position{
        Auto, Path, Query, Header, Cookie, Session, Form, Json,
    };
public:
    bool m_optional{false};
    IString m_optionalString;

    Position m_position{Auto};
    QMetaType::Type m_typeId{QMetaType::UnknownType};
    IString m_typeName;
    IString m_name;

protected:
    IString m_nameRaw;

public:
    std::function<void*(IRequest&)> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
};

$PackageWebCoreEnd

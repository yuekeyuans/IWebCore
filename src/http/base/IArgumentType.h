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
    Position m_position{Auto};
    QMetaType::Type m_typeId{QMetaType::UnknownType};
    std::string m_typeName;

    std::string m_nameRaw;
    std::string m_name;

public:
    std::function<void*(IRequest&)> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
};

$PackageWebCoreEnd

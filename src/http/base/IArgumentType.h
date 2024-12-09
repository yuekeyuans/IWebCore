#pragma once

#include "core/util/IHeaderUtil.h"

$PackageWebCoreBegin

class IRequest;
struct IArgumentType
{
    enum Position{
        Auto, Param, Url, Header, Body, Content, Cookie, Session,
    };
public:
    void* create(IRequest&) const;
    void destory(void*) const;

public:
    bool optional{false};
    Position position{Auto};
    QMetaType::Type typeId{QMetaType::UnknownType};
    std::string typeName;

    std::string nameRaw;
    std::string name;

    std::vector<std::string> m_arguments;   // 用于初始化的 arguements
protected:
    std::function<void*(IRequest&)> m_createFun{};
    std::function<void(void*)> m_destroyFun{};
};

$PackageWebCoreEnd

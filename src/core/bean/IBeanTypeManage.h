#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    using FromJson = std::function<bool(void*ptr, const IJson&)>;
    using ToJson =  std::function<IJson(void* ptr)>;
public:
    IBeanTypeManage() = default;

public:
    void registerBeanId(int id);
    void registerFromJson(int id, FromJson);
    void registerToJson(int id, ToJson);
    FromJson& getBeanFromJson(int id);
    ToJson& getBeanToJson(int id);
    bool isBeanIdExist(int id) const;

private:
    std::unordered_set<int> m_beanIds;
    std::unordered_map<int, FromJson> m_beanFromJson;
    std::unordered_map<int, ToJson> m_beanToJson;
};

$PackageWebCoreEnd


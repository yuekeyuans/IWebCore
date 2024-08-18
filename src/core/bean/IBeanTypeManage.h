#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <functional>
#include <unordered_set>
#include "IJson.h"

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    using ToJsonFun = std::function<IJson(void*, bool*)>;
    using LoadJsonFun = std::function<bool(void*, const IJson&)>;

public:
    IBeanTypeManage() = default;

public:
    void registerBeanId(int id);
    bool isBeanIdExist(int id);
    void registerToJsonFun(int id, ToJsonFun);
    void registerLoadJsonFun(int id, LoadJsonFun);
    ToJsonFun getToJsonFun(int id);
    LoadJsonFun getLoadJsonFun(int id);

private:
    std::unordered_set<int> m_beanIds;
    std::unordered_map<int, ToJsonFun> m_toJsonMap;
    std::unordered_map<int, LoadJsonFun> m_loadJsonMap;
};

$PackageWebCoreEnd


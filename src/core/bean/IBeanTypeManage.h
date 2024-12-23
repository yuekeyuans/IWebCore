#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    using BeanAssign = std::function<bool(void*ptr, const IJson&)>;
public:
    IBeanTypeManage() = default;

public:
    void registerBeanId(int id);
    void registerBeanAssign(int id, BeanAssign);
    BeanAssign& getBeanAssign(int id);
    bool isBeanIdExist(int id) const;

private:
    std::unordered_set<int> m_beanIds;
    std::unordered_map<int, BeanAssign> m_beanAssign;
};

$PackageWebCoreEnd


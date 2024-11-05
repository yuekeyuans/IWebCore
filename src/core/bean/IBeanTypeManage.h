#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    IBeanTypeManage() = default;

public:
    void registerBeanId(int id);
    bool isBeanIdExist(int id) const;

private:
    std::unordered_set<int> m_beanIds;
};

$PackageWebCoreEnd


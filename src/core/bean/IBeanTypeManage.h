#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

// TODO: 到时候看看这个可能被废弃掉！！！
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
    template<typename, bool, typename>
    friend class IBeanInterface;
    friend class IBeanTypeCheckTask;

public:
    IBeanTypeManage() = default;

public:
    bool isBeanIdExist(int id);

private:
    void registerBeanId(int id);

private:
    std::unordered_set<int> m_beanIds;
};

$PackageWebCoreEnd


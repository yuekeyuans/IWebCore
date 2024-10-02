#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

struct IBeanJsonSerializeWare;
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
    template<typename, bool, typename>
    friend class IBeanInterface;
    friend class IBeanTypeCheckTask;

public:
    IBeanTypeManage() = default;

public:
    bool isBeanIdExist(int id);
    void registerSerializeWare(IBeanJsonSerializeWare* ware);
    const std::vector<IBeanJsonSerializeWare*>& getSerializeWares();
private:
    void registerBeanId(int id);

private:
    std::unordered_set<int> m_beanIds;
    std::vector<IBeanJsonSerializeWare*> m_serializeWares;
};

$PackageWebCoreEnd


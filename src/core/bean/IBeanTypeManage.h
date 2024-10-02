#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

struct ITypeMarshalWare;
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
    template<typename, bool, typename>
    friend class IBeanInterface;
    friend class IBeanTypeCheckTask;

public:
    IBeanTypeManage() = default;

public:
    bool isBeanIdExist(int id);
    void registerSerializeWare(ITypeMarshalWare* ware);
    const std::vector<ITypeMarshalWare*>& getSerializeWares();
private:
    void registerBeanId(int id);

private:
    std::unordered_set<int> m_beanIds;
    std::vector<ITypeMarshalWare*> m_serializeWares;
};

$PackageWebCoreEnd


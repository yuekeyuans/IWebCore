#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <unordered_set>

$PackageWebCoreBegin

struct IBeanTypeMarshalWare;
class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    IBeanTypeManage() = default;

public:
    bool isBeanIdExist(int id) const;
    void registerSerializeWare(IBeanTypeMarshalWare* ware);
    const std::list<IBeanTypeMarshalWare*>& getSerializeWares() const;

private:
    void registerBeanId(int id);

private:
    std::unordered_set<int> m_beanIds;
    std::list<IBeanTypeMarshalWare*> m_serializeWares;
};

$PackageWebCoreEnd


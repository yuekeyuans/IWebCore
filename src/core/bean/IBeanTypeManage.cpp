#include "IBeanTypeManage.h"
#include "IBeanTypeMarshalWare.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

// NOTE: 通过这种方式，可以将一设置的对象冲掉
void IBeanTypeManage::registerSerializeWare(IBeanTypeMarshalWare *ware)
{
    m_serializeWares.push_front(ware);
}

const std::list<IBeanTypeMarshalWare *> &IBeanTypeManage::getSerializeWares() const
{
    return m_serializeWares;
}

bool IBeanTypeManage::isBeanIdExist(int id) const
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

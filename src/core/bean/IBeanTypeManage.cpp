#include "IBeanTypeManage.h"
#include "ITypeMarshalWare.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

// 通过这种方式，可以将一设置的对象冲掉
void IBeanTypeManage::registerSerializeWare(ITypeMarshalWare *ware)
{
    m_serializeWares.push_front(ware);
}

const std::list<ITypeMarshalWare *> &IBeanTypeManage::getSerializeWares()
{
    return m_serializeWares;
}

bool IBeanTypeManage::isBeanIdExist(int id)
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

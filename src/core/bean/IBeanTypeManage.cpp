#include "IBeanTypeManage.h"
#include "ITypeMarshalWare.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

void IBeanTypeManage::registerSerializeWare(ITypeMarshalWare *ware)
{
    m_serializeWares.push_back(ware);
}

const std::vector<ITypeMarshalWare *> &IBeanTypeManage::getSerializeWares()
{
    return m_serializeWares;
}

bool IBeanTypeManage::isBeanIdExist(int id)
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

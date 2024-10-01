#include "IBeanTypeManage.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

bool IBeanTypeManage::isBeanIdExist(int id)
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

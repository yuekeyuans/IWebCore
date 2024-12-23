#include "IBeanTypeManage.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

void IBeanTypeManage::registerBeanAssign(int id, IBeanTypeManage::BeanAssign assign)
{
    m_beanAssign[id] = assign;
}

IBeanTypeManage::BeanAssign &IBeanTypeManage::getBeanAssign(int id)
{
    return m_beanAssign[id];
}

bool IBeanTypeManage::isBeanIdExist(int id) const
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

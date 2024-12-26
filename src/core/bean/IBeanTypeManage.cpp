#include "IBeanTypeManage.h"

$PackageWebCoreBegin

void IBeanTypeManage::registerBeanId(int id)
{
    m_beanIds.insert(id);
}

void IBeanTypeManage::registerFromJson(int id, IBeanTypeManage::FromJson assign)
{
    m_beanFromJson[id] = assign;
}

void IBeanTypeManage::registerToJson(int id, IBeanTypeManage::ToJson fetch)
{
    m_beanToJson[id] = fetch;
}

IBeanTypeManage::FromJson &IBeanTypeManage::getBeanFromJson(int id)
{
    return m_beanFromJson[id];
}

IBeanTypeManage::ToJson &IBeanTypeManage::getBeanToJson(int id)
{
    return m_beanToJson[id];
}

bool IBeanTypeManage::isBeanIdExist(int id) const
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

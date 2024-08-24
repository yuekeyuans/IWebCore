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

void IBeanTypeManage::registerToJsonFun(int id, IBeanTypeManage::ToJsonFun fun)
{
    m_toJsonMap[id] = std::move(fun);
}

void IBeanTypeManage::registerLoadJsonFun(int id, IBeanTypeManage::LoadJsonFun fun)
{
    m_loadJsonMap[id] = std::move(fun);
}

void IBeanTypeManage::registerBeanProperties(int id, std::vector<QMetaProperty> properties)
{
    m_propertiesMap[id] = std::move(properties);
}

IBeanTypeManage::ToJsonFun IBeanTypeManage::getToJsonFun(int id)
{
    return m_toJsonMap[id];
}

IBeanTypeManage::LoadJsonFun IBeanTypeManage::getLoadJsonFun(int id)
{
    return m_loadJsonMap[id];
}

$PackageWebCoreEnd

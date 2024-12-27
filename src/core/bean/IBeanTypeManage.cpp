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

IBeanTypeManage::FromJson IBeanTypeManage::getBeanFromJson(int id)
{
    if(m_beanFromJson.contains(id)){
        return m_beanFromJson[id];
    }
    qFatal("not exist");
    return nullptr;
}

IBeanTypeManage::ToJson IBeanTypeManage::getBeanToJson(int id)
{
    if(m_beanToJson.contains(id)){
        return m_beanToJson[id];
    }
    qFatal("not exist");
    return nullptr;
}

bool IBeanTypeManage::isBeanIdExist(int id) const
{
    return m_beanIds.find(id) != m_beanIds.end();
}

$PackageWebCoreEnd

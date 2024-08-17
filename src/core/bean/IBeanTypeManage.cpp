#include "IBeanTypeManage.h"

$PackageWebCoreBegin

//void IBeanTypeManage::registerBeanType(const QString &typeName)
//{
//    auto name = typeName.split(' ').last();
//    auto inst = instance();
//    inst->m_beanNames.append(name);
//}

//bool IBeanTypeManage::containBean(const QString &typeName)
//{
//    auto inst = instance();
//    QString name = typeName;
//    const QStringList& beanNames = inst->m_beanNames;
//    if(typeName.endsWith("&")){
//        name = typeName.mid(0, typeName.length() -1);
//    }
//    if(beanNames.contains(name)){
//        return true;
//    }else{
//        for(auto beanName : beanNames){
//            if(beanName.endsWith(name)){
//                return true;
//            }
//        }
//    }
//    return false;
//}

void IBeanTypeManage::registerBeanId(int id)
{
    if(!m_beanIds.contains(id)){
        m_beanIds.append(id);
    }
}

bool IBeanTypeManage::isBeanIdExist(int id)
{
    return m_beanIds.contains(id);
}

void IBeanTypeManage::registerToJsonFun(int id, IBeanTypeManage::ToJsonFun fun)
{
    m_toJsonMap[id] = fun;
}

void IBeanTypeManage::registerLoadJsonFun(int id, IBeanTypeManage::LoadJsonFun fun)
{
    m_loadJsonMap[id] = fun;
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

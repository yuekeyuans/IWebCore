#include "ITypeManage.h"

$PackageWebCoreBegin

void ITypeManage::registerBeanType(const QString &typeName)
{
    auto name = typeName.split(' ').last();
    auto inst = instance();
    inst->m_beanNames.append(name);
}

void ITypeManage::registerNamespace(const QString &nmspace)
{
    auto inst = instance();
    inst->m_nameSpaces.append(nmspace);
}

// 这一个不能够完全判断一个 typeName 就是一个bean, 也会有出错的时候，但是忽略掉。
bool ITypeManage::containBean(const QString &typeName)
{
    auto inst = instance();
    QString name = typeName;
    const auto& beanNames = inst->m_beanNames;
    if(typeName.endsWith("&")){
        name = typeName.mid(0, typeName.length() -1);
    }
    if(beanNames.contains(name)){
        return true;
    }else{
        for(auto beanName : beanNames){
            if(beanName.endsWith(name)){
                return true;
            }
        }
    }
    return false;
}


$PackageWebCoreEnd

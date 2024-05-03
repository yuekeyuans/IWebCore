#include "IBeanTypeManage.h"

$PackageWebCoreBegin

class IBeanTypeManageImpl
{
public:
    QStringList m_beanNames;
};

IBeanTypeManage::IBeanTypeManage()
    : d_ptr(std::make_shared<IBeanTypeManageImpl>())
{
}

void IBeanTypeManage::registerBeanType(const QString &typeName)
{
    auto name = typeName.split(' ').last();
    auto inst = instance();
    inst->d_ptr->m_beanNames.append(name);
}

bool IBeanTypeManage::containBean(const QString &typeName)
{
    auto inst = instance();
    QString name = typeName;
    const QStringList& beanNames = inst->d_ptr->m_beanNames;
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

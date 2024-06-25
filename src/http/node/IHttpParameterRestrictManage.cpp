#include "IHttpParameterRestrictManage.h"
#include "http/node/IHttpParameterRestrictInterface.h"

$PackageWebCoreBegin

void IHttpParameterRestrictManage::addRestrict(IHttpParameterRestrictInterface *obj)
{
    m_map[obj->tag()] = obj;
}

QStringList IHttpParameterRestrictManage::getRestrictNames() const
{
    return m_map.keys();
}

IHttpParameterRestrictInterface *IHttpParameterRestrictManage::getRestrict(const QString &name)
{
    if(m_map.contains(name)){
        return m_map[name];
    }
    return nullptr;
}

$PackageWebCoreEnd

#include "IBeanTypeCheckTask.h"
#include "core/bean/IBeanTypeManage.h"

$PackageWebCoreBegin

void IBeanTypeCheckTask::task()
{
//    for(auto id : IBeanTypeManage::instance()->m_beanIds){
//        qDebug() << id  << QMetaType::typeName(id);
//    }
}

double IBeanTypeCheckTask::order() const
{
    return 0;
}

$PackageWebCoreEnd

#include "IHttpPrintTraceTask.h"
#include "core/config/IProfileImport.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

void IHttpPrintTraceTask::task()
{
    $Bool condition{"/http/printTrace", false};
    if(condition.value()){
        IHttpManage::travalPrintUrlTree();
    }
}

$PackageWebCoreEnd

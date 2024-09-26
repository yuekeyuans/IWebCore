#include "IHttpPrintTraceTask.h"
#include "core/config/IProfileImport.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

void IHttpPrintTraceTask::task()
{
    $Bool condition{"/http/printTrace"};
    if(condition.isFound() && condition){
        IHttpManage::travalPrintUrlTree();
    }
}

$PackageWebCoreEnd

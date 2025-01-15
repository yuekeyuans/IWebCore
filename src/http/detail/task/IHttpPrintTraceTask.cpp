#include "IHttpPrintTraceTask.h"
#include "core/config/IProfileImport.h"
#include "http/IHttpManage.h"

$PackageWebCoreBegin

void IHttpPrintTraceTask::$task()
{
    $Bool condition{"/http/printTrace", false};
    if(condition.value()){
        IHttpManage::instance()->printMappingTrace();
    }
}

$PackageWebCoreEnd

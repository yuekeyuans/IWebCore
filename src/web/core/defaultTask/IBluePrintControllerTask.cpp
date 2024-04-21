#include "IBluePrintControllerTask.h"
#include "core/config/IProfileImport.h"
#include "web/controller/IHttpManage.h"

$PackageWebCoreBegin

void IBluePrintControllerTask::task()
{
    $Bool condition{"http.printTrace"};
    if(condition.isFound() && condition){
        IHttpManage::travalPrintUrlTree();
    }
}

$PackageWebCoreEnd

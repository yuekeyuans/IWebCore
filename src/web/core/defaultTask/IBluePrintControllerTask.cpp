#include "IBluePrintControllerTask.h"
#include "core/config/IProfileImport.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IBluePrintControllerTask::task()
{
    $Bool condition{"http.printTrace"};
    if(condition.isFound() && condition){
        IControllerManage::travalPrintUrlTree();
    }
}

$PackageWebCoreEnd

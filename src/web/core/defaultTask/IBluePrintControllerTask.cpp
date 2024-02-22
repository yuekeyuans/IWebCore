#include "IBluePrintControllerTask.h"
#include "core/config/IContextImport.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IBluePrintControllerTask::task()
{
    $ContextBool condition{"SYSTEM_BLUE_PRINT", false};
    if(condition.isFound() && condition){
        IControllerManage::travalPrintUrlTree();
    }
}

$PackageWebCoreEnd

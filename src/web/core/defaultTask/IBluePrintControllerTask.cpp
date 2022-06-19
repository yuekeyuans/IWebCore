#include "IBluePrintControllerTask.h"

#include "core/asset/IGlobalAsset.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskManage.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

$UseGlobalAsset()

IBluePrintControllerTask::IBluePrintControllerTask()
{
    registerTask();
}

void IBluePrintControllerTask::registerTask()
{
    static auto task = [](){
        bool convertOk;
        auto value = IConfigurationManage::getValue("SYSTEM_BLUE_PRINT", &convertOk, SystemConfigurationGroup);
        if(!convertOk){
            return;
        }

        if(!value.isBool()){
            $GlobalAsset->fatal(IGlobalAsset::EnableBluePrintParamError);
        }
        if(value.toBool()){
            IControllerManage::travalPrintUrlTree();
        }
    };
    ITaskManage::registerBluePrint(task);
}

$PackageWebCoreEnd

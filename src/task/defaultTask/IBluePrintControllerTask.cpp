#include "IBluePrintControllerTask.h"

#include "configuration/IConfigurationManage.h"
#include "controller/IControllerManage.h"
#include "core/assertion/IAssertPreProcessor.h"
#include "task/ITaskManage.h"

$PackageWebCoreBegin

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
            $AssertFatal(EnableBluePrint_param_error); // TODO: 这个必须被处理掉
        }
        if(value.toBool()){
            IControllerManage::travalPrintUrlTree();
        }
    };
    ITaskManage::registerBluePrint(task);
}

$PackageWebCoreEnd

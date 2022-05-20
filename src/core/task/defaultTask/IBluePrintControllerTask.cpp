#include "IBluePrintControllerTask.h"

#include "core/assertion/IAssertPreProcessor.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskManage.h"
#include "web/controller/IControllerManage.h"

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

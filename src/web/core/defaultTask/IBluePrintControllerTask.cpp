#include "IBluePrintControllerTask.h"

#include "core/ast/IGlobalAst.h"
#include "core/configuration/IConfigurationManage.h"
#include "core/task/ITaskManage.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

$UseGlobalAst()

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
            $GlobalAst->fatal(IGlobalAst::EnableBluePrintParamError);
        }
        if(value.toBool()){
            IControllerManage::travalPrintUrlTree();
        }
    };
    ITaskManage::registerBluePrint(task);
}

$PackageWebCoreEnd

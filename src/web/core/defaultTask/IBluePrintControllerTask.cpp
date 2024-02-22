//#include "IBluePrintControllerTask.h"

//#include "core/assert/IGlobalAssert.h"
//#include "core/task/ITaskManage.h"
//#include "web/controller/IControllerManage.h"

//$PackageWebCoreBegin

//$UseGlobalAssert()

//IBluePrintControllerTask::IBluePrintControllerTask()
//{
//    registerTask();
//}

//void IBluePrintControllerTask::registerTask()
//{
//    static auto task = [](){
//        bool convertOk;
//        auto value = IConfi5gurationManage::getValue("SYSTEM_BLUE_PRINT", &convertOk, SystemContextGroup);
//        if(!convertOk){
//            return;
//        }

//        if(!value.isBool()){
//            $GlobalAssert->fatal(IGlobalAssert::EnableBluePrintParamError);
//        }
//        if(value.toBool()){
//            IControllerManage::travalPrintUrlTree();
//        }
//    };
////    ITaskManage::registerBluePrint(task);
//}

//$PackageWebCoreEnd

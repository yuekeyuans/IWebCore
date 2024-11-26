#include "IUnitTestTask.h"
#include "core/test/IUnitTestManage.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

void IUnitTestTask::$task()
{
    $ContextBool enabled("/test/unittest/enabled", false);
    if(! (*enabled)){
        qDebug() << CLASS_NAME << "disabled";
        return;
    }
    IUnitTestManage::instance()->invokeTests();
}

$PackageWebCoreEnd

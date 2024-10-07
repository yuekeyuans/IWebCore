#include "IHttpFileServiceTask.h"
#include "core/config/IProfileImport.h"
#include "http/controller/IHttpManage.h"

$PackageWebCoreBegin

void IHttpFileServiceTask::$task()
{
    $QString staticPath{"/http/fileService/path"};
    if(staticPath.value().isEmpty()){
        return;
    }

    $QString staticUrl{"/http/fileService/url"};
    if(staticUrl.value().isEmpty()){
        return;
    }
    IHttpManage::instance()->registerStaticFiles(*staticPath, *staticUrl);
}

$PackageWebCoreEnd

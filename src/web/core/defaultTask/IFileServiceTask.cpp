#include "IFileServiceTask.h"
#include "core/config/IProfileImport.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IFileServiceTask::task()
{
    $QString staticPath{"http.fileService.path"};
    if(!staticPath.isFound() || staticPath.value().isEmpty()){
        return;
    }

    $QString staticUrl{"http.fileService.url"};
    if(!staticUrl.isFound() || staticUrl.value().isEmpty()){
        return;
    }
    IControllerManage::instance()->registerStaticFiles(staticPath, staticUrl);
}

$PackageWebCoreEnd

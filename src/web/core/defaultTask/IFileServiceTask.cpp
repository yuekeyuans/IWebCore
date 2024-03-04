#include "IFileServiceTask.h"
#include "core/config/IProfileImport.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IFileServiceTask::task()
{
    $QString staticPath{"http.fileService.path"};
    if(!staticPath.isFound()){
        return;
    }

    $QString staticUrl{"http.fileService.url", "/"};
    IControllerManage::instance()->registerStaticFiles(staticPath, staticUrl);
}

$PackageWebCoreEnd

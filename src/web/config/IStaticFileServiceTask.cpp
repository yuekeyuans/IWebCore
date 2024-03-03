#include "IStaticFileServiceTask.h"
#include "core/config/IProfileImport.h"
#include "web/controller/IControllerManage.h"

$PackageWebCoreBegin

void IStaticFileServiceTask::task()
{
    $QString staticPath{"http.fileService.path"};
    qDebug() << staticPath.isFound() << staticPath;

    if(!staticPath.isFound()){
        return;
    }

    $QString staticUrl{"http.fileService.url", "/"};
    IControllerManage::instance()->registerStaticFiles(staticPath, staticUrl);
}

$PackageWebCoreEnd

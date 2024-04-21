#include "IFileServiceTask.h"
#include "core/config/IProfileImport.h"
#include "http/controller/IHttpManage.h"

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
    IHttpManage::instance()->registerStaticFiles(staticPath, staticUrl);
}

$PackageWebCoreEnd

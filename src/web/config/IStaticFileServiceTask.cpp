#include "IStaticFileServiceTask.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

void IStaticFileServiceTask::task()
{
    $QString staticPath{"http.fileService.path"};
    qDebug() << staticPath.isFound() << staticPath;

    $QString staticUrl{"http.fileService.url"};
    qDebug() << staticUrl.isFound() << staticUrl;
}

$PackageWebCoreEnd

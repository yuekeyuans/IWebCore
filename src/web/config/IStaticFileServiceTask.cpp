#include "IStaticFileServiceTask.h"
#include "core/config/IProfileImport.h"

$PackageWebCoreBegin

void IStaticFileServiceTask::task()
{
    $QString staticPath{"http.staticLocation"};
    qDebug() << staticPath.isFound() << staticPath;
}

$PackageWebCoreEnd

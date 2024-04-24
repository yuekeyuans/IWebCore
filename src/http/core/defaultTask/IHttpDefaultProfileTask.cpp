#include "IHttpDefaultProfileTask.h"
#include "core/base/IConvertUtil.h"
#include "core/config/IProfileManage.h"
#include "core/base/IFileUtil.h"

$PackageWebCoreBegin

double IHttpDefaultProfileTask::order() const
{
    return 1;
}

QJsonValue IHttpDefaultProfileTask::config()
{
    auto content = IFileUtil::readFileAsString(":/resource/defaultWebConfig.json");
    IResult<QJsonObject> json = IConvertUtil::toJsonObject(content);
    return json.value();
}

$PackageWebCoreEnd

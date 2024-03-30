#include "IWebDefaultProfileTask.h"
#include "core/base/IConvertUtil.h"
#include "core/config/IProfileManage.h"
#include "core/base/IFileUtil.h"

$PackageWebCoreBegin

double IWebDefaultProfileTask::order() const
{
    return 1;
}

QJsonValue IWebDefaultProfileTask::config()
{
    auto content = IFileUtil::readFileAsString(":/resource/defaultWebConfig.json");
    IResult<QJsonObject> json = IConvertUtil::toJsonObject(content);
    return json.value();
}

$PackageWebCoreEnd

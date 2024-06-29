#include "IHttpDefaultProfileTask.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/config/IProfileManage.h"
#include "core/util/IFileUtil.h"

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

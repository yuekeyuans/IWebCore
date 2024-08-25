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

IJson IHttpDefaultProfileTask::config()
{
    IResult<QString> content = IFileUtil::readFileAsString(":/resource/defaultWebConfig.json");
    if(!content){
        return nullptr;
    }
    auto stdStringContent = (*content).toStdString();
    if(IJson::accept(stdStringContent)){
        return IJson::parse(stdStringContent);
    }

    return nullptr;
}

$PackageWebCoreEnd

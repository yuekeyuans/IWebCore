#include "IHttpDefaultProfileTask.h"
#include "core/config/IProfileManage.h"
#include "core/util/IFileUtil.h"
#include "core/config/IConfigAbort.h"

$PackageWebCoreBegin

double IHttpDefaultProfileTask::order() const
{
    return 1;
}

IJson IHttpDefaultProfileTask::config()
{
    if(!QFile(CONFIG_FILE_PATH).exists()){
        return nullptr;
    }

    IResult<QString> content = IFileUtil::readFileAsString(CONFIG_FILE_PATH);
    if(!content){
        return nullptr;
    }

    auto stdStringContent = (*content).toStdString();
    try {
        IJson parsedJson = IJson::parse(stdStringContent);
        return parsedJson;
    } catch (nlohmann::json::parse_error& e) {
        QString tip  = QString("File At: ") + CONFIG_FILE_PATH + " Reason:" + e.what();
        IConfigAbort::abortConfigurationResolveJsonError(tip, $ISourceLocation);
    }

    return nullptr;
}

$PackageWebCoreEnd

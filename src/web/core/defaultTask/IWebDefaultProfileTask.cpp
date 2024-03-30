#include "IWebDefaultProfileTask.h"
#include "core/base/IConvertUtil.h"
#include "core/config/IProfileManage.h"

$PackageWebCoreBegin

static constexpr char PROFILE_CONFIG[] =
R"(
{
    "http": {
        "ip": "127.0.0.1",
        "port": 8550,
        "printTrace": true,
        "defaultPageNames": [
            "index.html",
            "index.htm",
            "default.html",
            "default.htm"
        ],
        "fileService": {
            "folderHandled": true,
            "staticMapping" : true,
            "path" : "",
            "url" : "/",
            "contentDisposition" : {
                "enabled" : false,
                "suffixes" : []
            }
        },
        "template" : {
            "nody" : {
                "directories" : []
            }
        }
    }
}

)";

double IWebDefaultProfileTask::order() const
{
    return 1;
}

QJsonValue IWebDefaultProfileTask::config()
{
    IResult<QJsonObject> json = IConvertUtil::toJsonObject(PROFILE_CONFIG);
    return json.value();
}

$PackageWebCoreEnd

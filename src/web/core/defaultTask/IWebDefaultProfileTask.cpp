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
            "directoryHandled": true
        }
    }
}



)";

double IWebDefaultProfileTask::order() const
{
    return 1;
}

void IWebDefaultProfileTask::task()
{
    IResult<QJsonObject> json = IConvertUtil::toJsonObject(PROFILE_CONFIG);
    if(json.isOk()){
        IProfileManage::instance()->addConfig(json.m_value);
    }else{
        qFatal("default profile config error");
    }
}


$PackageWebCoreEnd

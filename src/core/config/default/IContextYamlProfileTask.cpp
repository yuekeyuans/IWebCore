#include "IContextYamlProfileTask.h"
#include "core/util/IFileUtil.h"
#include "core/config/IProfileManage.h"
#include "core/config/IContextImport.h"
#include "core/config/IConfigAbort.h"
#include "Yaml.hpp"

$PackageWebCoreBegin


IJson IContextYamlProfileTask::config()
{
    $ContextBool enableConfigFiles{"config.enableConfigFiles", false};
    if(!enableConfigFiles.isFound() || !enableConfigFiles){
        return {};
    }

    auto paths = getValidatedPaths();
    for(auto path : paths){
        bool ok;
        auto obj = parseYamlFile(path, ok);
        if(ok){
            IProfileManage::instance()->addConfig(obj);
        }
    }

    return {};
}

double IContextYamlProfileTask::order() const
{
    return 99.0;
}

QStringList IContextYamlProfileTask::nameFilters() const
{
    return {"*.yaml", "*.yml"};
}

IJson IContextYamlProfileTask::parseYamlFile(const QString &path, bool& ok)
{
    QString content = IFileUtil::readFileAsString(path, ok);
    if(!ok){
        IConfigAbort::abortConfigurationResolveJsonError($ISourceLocation);
    }

    IJson json = IJson::object();

    return json;
}

$PackageWebCoreEnd

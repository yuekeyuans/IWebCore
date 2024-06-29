#include "IContextJsonProfileTask.h"
#include "core/util/IFileUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/config/IProfileManage.h"
#include "core/config/IContextImport.h"
#include "core/abort/IAbortInterface.h"

$PackageWebCoreBegin

class IContextAbort : public IAbortInterface<IContextAbort>
{
    $AsAbort(
        ConfigurationResolveJsonError
    )
protected:
    virtual QMap<int, QString> abortDescription() const final{
        return {
            {ConfigurationResolveJsonError, ""},

        };
    }
};

QJsonValue IContextJsonProfileTask::config()
{
    $ContextBool enableConfigFiles{"config.enableConfigFiles", false};
    if(!enableConfigFiles.isFound() || !enableConfigFiles){
        return {};
    }

    auto paths = getValidatedPaths();
    for(auto path : paths){
        auto obj = parseJsonFile(path);
        IProfileManage::instance()->addConfig(obj);
    }

    return {};
}

double IContextJsonProfileTask::order() const
{
    return 99.0;
}

QStringList IContextJsonProfileTask::nameFilters() const
{
    return {"*.json"};
}

QJsonObject IContextJsonProfileTask::parseJsonFile(const QString &path) const
{
    QJsonObject obj;
    bool ok;
    QString content = IFileUtil::readFileAsString(path, ok);
    if(!ok){
        IContextAbort::abortConfigurationResolveJsonError($ISourceLocation);
        return obj;
    }

    obj = IJsonUtil::toJsonObject(content, ok);
    if(!ok){
        IContextAbort::abortConfigurationResolveJsonError("path:" + path, $ISourceLocation);
    }
    return obj;
}

$PackageWebCoreEnd

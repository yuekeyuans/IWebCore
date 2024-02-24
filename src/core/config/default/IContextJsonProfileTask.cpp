#include "IContextJsonProfileTask.h"
#include "core/assert/IGlobalAssert.h"
#include "core/base/IFileUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/config/IProfileManage.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

$UseGlobalAssert()

QJsonValue IContextJsonProfileTask::config()
{
    $ContextBool enableConfigFiles{"config.enableConfigFiles", false};
    if(!enableConfigFiles){
        return {};
    }

    auto paths = getValidatedJsonPaths();
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

QStringList IContextJsonProfileTask::getConfigDirs() const
{
    QStringList ret;
    $Context<QJsonObject> paths{"config.configFilePaths"};
    if(!paths.isFound()){
        return ret;
    }

    QStringList keys = paths.value().keys();
    for(const auto& key : keys){
        ret.append(paths.value()[key].toString());
    }
    return ret;
}

QStringList IContextJsonProfileTask::getJsonPaths() const
{
    QStringList filesPaths;
    auto dirs = getConfigDirs();
    for(auto dirPath : dirs){
        QDir dir(dirPath);
        auto entries = dir.entryInfoList({"*.json"});
        for(const auto& fileInfo : entries){
            if(!fileInfo.isDir() && fileInfo.filePath().endsWith("config.json")){
                filesPaths.append(fileInfo.filePath());
            }
        }
    }
    return filesPaths;
}

QStringList IContextJsonProfileTask::getValidatedJsonPaths() const
{
    auto paths = getJsonPaths();

    $ContextQString exp{"config.configFilesFilter", ""};
    if(!exp.isFound() || exp == ""){
        return paths;
    }

    QStringList ret;
    QRegExp reg(exp.value());
    reg.setPatternSyntax(QRegExp::Wildcard);
    for(const auto& path : paths){
        if(reg.exactMatch(QFileInfo(path).fileName())){
            ret.append(path);
        }
    }
    return ret;
}

QJsonObject IContextJsonProfileTask::parseJsonFile(const QString &path) const
{
    QJsonObject obj;
    bool ok;
    QString content = IFileUtil::readFileAsString(path, ok);
    if(!ok){
        $GlobalAssert->fatal("ConfigurationResolveJsonError");
        return obj;
    }

    obj = IJsonUtil::toJsonObject(content, ok);
    if(!ok){
        IAssertInfo info;
        info.reason = path;
        $GlobalAssert->fatal("ConfigurationResolveJsonError", info);
    }
    return obj;
}

$PackageWebCoreEnd

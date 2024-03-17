#include "ILoadProfileFileUnit.h"
#include "core/config/IContextImport.h"
#include <QRegularExpression>

$PackageWebCoreBegin

QStringList ILoadProfileFileUnit::getValidatedPaths() const
{
    auto paths = getConfigFiles();

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

QStringList ILoadProfileFileUnit::getConfigDirs() const
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

QStringList ILoadProfileFileUnit::getConfigFiles() const
{
    QStringList filesPaths;
    auto dirs = getConfigDirs();
    for(auto dirPath : dirs){
        QDir dir(dirPath);
        auto entries = dir.entryInfoList(nameFilters());
        for(const auto& fileInfo : entries){
            if(fileInfo.isFile()){
                filesPaths.append(fileInfo.filePath());
            }
        }
    }
    return filesPaths;
}

$PackageWebCoreEnd

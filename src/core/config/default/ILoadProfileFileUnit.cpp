#include "ILoadProfileFileUnit.h"
#include "core/config/IContextImport.h"
#include <QRegularExpression>

$PackageWebCoreBegin

QStringList ILoadProfileFileUnit::getFilteredPaths() const
{
    $ContextMapStdString map{"/config/configFileFilters"};
    if(map.value().empty()){
        return {};
    }

    QList<QRegExp> filters;
    for(const auto &[key, val] : map.value()){
        QRegExp reg(QString::fromStdString(val));
        reg.setPatternSyntax(QRegExp::Wildcard);
        filters.append(reg);
    }

    auto paths = getConfigFiles();
    if(paths.isEmpty()){
        return {};
    }

    QStringList ret;

    for(const auto& path : paths){
        for(auto filter : filters){
            if(filter.exactMatch(QFileInfo(path).fileName())){
                ret.append(path);
                break;
            }
        }
    }
    return ret;
}

QStringList ILoadProfileFileUnit::getConfigDirs() const
{

    $ContextMapStdString paths{"/config/configFilePaths"};
    if(paths.value().empty()){
        return {};
    }
    QStringList ret;
    for(auto pair : *paths){
        ret.append(QString::fromStdString(pair.second));
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

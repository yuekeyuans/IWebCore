#include "ILoadProfileFileUnit.h"
#include "core/config/IContextImport.h"
#include <QRegularExpression>

$PackageWebCoreBegin

QStringList ILoadProfileFileUnit::getValidatedPaths() const
{
    auto paths = getConfigFiles();

    $ContextQString exp{"/config/configFilesFilter", ""};
    if(exp.value().isEmpty()){
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

// TODO: 这个需要重新设计,之后在看
QStringList ILoadProfileFileUnit::getConfigDirs() const
{
//    $Context<IJson> paths{"/config/configFilePaths"};
//    if(!paths.value().is_object()){
//        return {};
//    }

    QStringList ret;
//    for(auto&[key, value] : paths.value().items()){
//        ret.append(QString::fromStdString(value.get<std::string>()));
//    }

    return ret;

//    QStringList keys = paths.value().keys();
//    for(const auto& key : keys){
//        ret.append(paths.value()[key].toString());
//    }
//    return ret;
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

#include "IContextYamlProfileTask.h"
#include "core/assert/IGlobalAssert.h"
#include "core/base/IFileUtil.h"
#include "core/config/yaml/IYamlUtil.h"
#include "core/config/IProfileManage.h"

$PackageWebCoreBegin

$UseGlobalAssert()

QJsonValue IContextYamlProfileTask::config()
{
    auto paths = getYamlPaths();
    for(auto path : paths){
        auto obj = parseYamlFile(path);
        IProfileManage::instance()->addConfig(obj);
        qDebug() << "Load Configuration:\t" << path;
    }

    return {};
}

QStringList IContextYamlProfileTask::getYamlPaths(){
    QStringList ret;
    auto entries = QDir(":/").entryInfoList({"*.yaml"});
    for(auto fileInfo : entries){
        if(!fileInfo.isDir() && fileInfo.filePath().endsWith("config.yaml")){
            ret.append(fileInfo.filePath());
        }
    }
    return ret;
}

QJsonObject IContextYamlProfileTask::parseYamlFile(const QString &path){
    QJsonObject obj;

    bool convertOk;
    QString content = IFileUtil::readFileAsString(path);
    obj = IYamlUtil::toJsonObject(content, &convertOk);
    if(!convertOk){
        IAssertInfo info;
        info.reason = path;
        $GlobalAssert->fatal(IGlobalAssert::ConfigurationResolveJsonError, info);
    }
    return obj;
}

$PackageWebCoreEnd

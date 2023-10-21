#include "IContextYamlConfigTask.h"
#include "core/assert/IGlobalAssert.h"
#include "core/base/IFileUtil.h"
#include "core/context/yaml/IYamlUtil.h"
#include "core/context/IContextManage.h"
#include "core/profile/IProfileManage.h"

$PackageWebCoreBegin

$UseGlobalAssert()

QJsonValue IContextYamlConfigTask::getApplicationConfig()
{
    auto paths = getYamlPaths();
    for(auto path : paths){
        auto obj = parseYamlFile(path);
        IProfileManage::instance()->addConfig(obj);
        qDebug() << "Load Configuration:\t" << path;
    }

    return {};
}

QStringList IContextYamlConfigTask::getYamlPaths(){
    QStringList ret;
    auto entries = QDir(":/").entryInfoList({"*.yaml"});
    for(auto fileInfo : entries){
        if(!fileInfo.isDir() && fileInfo.filePath().endsWith("config.yaml")){
            ret.append(fileInfo.filePath());
        }
    }
    return ret;
}

QJsonObject IContextYamlConfigTask::parseYamlFile(const QString &path){
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

#include "IConfigurationResourceAutoLoader.h"

#include "IConfigurationManage.h"
#include "yaml/IYamlUtil.h"
#include "base/IFileUtil.h"
#include "base/IJsonUtil.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

// 具体执行者
namespace Loader{
    void loadSystemEnvironment();
    void loadJson();
    void loadYaml();

    QStringList getJsonPaths();
    QStringList getYamlPaths();
    QJsonObject getSystemEnvironment();

    QJsonObject parseJsonFile(const QString& path);
    QJsonObject parseYamlFile(const QString& path);
}

QString IConfigurationResourceAutoLoader::taskFinishTip()
{
    return "Auto Load Resource Task Finish";
}

void IConfigurationResourceAutoLoader::task()
{
    loadSystemEnvironment();
    loadJson();
    loadYaml();
}

void IConfigurationResourceAutoLoader::loadSystemEnvironment()
{
    Loader::loadSystemEnvironment();
}

void IConfigurationResourceAutoLoader::loadJson()
{
    Loader::loadJson();
}

void IConfigurationResourceAutoLoader::loadYaml()
{
    Loader::loadYaml();
}

void Loader::loadSystemEnvironment(){
    auto obj = getSystemEnvironment();
    IConfigurationManage::registerConfiguration(SystemConfigurationGroup, obj);
    qDebug() << "Load SystemEnvironment";
}

void Loader::loadJson(){
    auto paths = getJsonPaths();
    for(auto path : paths){
        auto obj = parseJsonFile(path);
        IConfigurationManage::registerConfiguration(ApplicationConfigurationGroup, obj);
        qDebug() << "Load Configuration:\t" << path;
    }
}

void Loader::loadYaml(){
    auto paths = getYamlPaths();
    for(auto path : paths){
        auto obj = parseYamlFile(path);
        IConfigurationManage::registerConfiguration(ApplicationConfigurationGroup, obj);
        qDebug() << "Load Configuration:\t" << path;
    }
}

// TODO: 添加 自定义path. 自定义path 需要 systemSetting configuration 中间获取。
QStringList Loader::getJsonPaths(){
    QStringList ret;
    QDir dir(":/");
    auto entries = dir.entryInfoList({"*.json"});
    for(auto fileInfo : entries){
        if(!fileInfo.isDir() && fileInfo.filePath().endsWith("config.json")){
            ret.append(fileInfo.filePath());
        }
    }
    return ret;
}

QStringList Loader::getYamlPaths(){
    QStringList ret;
    auto entries = QDir(":/").entryInfoList({"*.yaml"});
    for(auto fileInfo : entries){
        if(!fileInfo.isDir() && fileInfo.filePath().endsWith("config.yaml")){
            ret.append(fileInfo.filePath());
        }
    }
    return ret;
}

QJsonObject Loader::getSystemEnvironment(){
    QJsonObject obj;
    QStringList environment = QProcess::systemEnvironment();
    for(auto str : environment)
    {
        auto index = str.indexOf('=');
        auto key = str.left(index);
        auto value = str.mid(index +1 );
        obj[key] = value;
    }
    return obj;
}

QJsonObject Loader::parseJsonFile(const QString& path)
{
    QJsonObject obj;

    bool convertOk = true;
    QString content = IFileUtil::readFileAsString(path);
    obj = IJsonUtil::toJsonObject(content, &convertOk);
    if(!convertOk){
        IAssertInfo info;
        info.reason = path;
        $GlobalAssert->fatal(IGlobalAssert::ConfigurationResolveJsonError, info);
    }
    return obj;
}

QJsonObject Loader::parseYamlFile(const QString& path){
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

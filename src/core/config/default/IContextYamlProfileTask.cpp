#include "IContextYamlProfileTask.h"
#include "core/base/IFileUtil.h"
#include "core/config/IProfileManage.h"
#include "core/config/IContextImport.h"
#include "core/config/IConfigAbort.h"
#include "Yaml.hpp"

$PackageWebCoreBegin

static QJsonObject toObject(const Yaml::Node& node);
static QJsonValue toValue( const Yaml::Node& node);

static QJsonArray toArray(const Yaml::Node& node){
    QJsonArray array;
    for(auto it=node.Begin(); it!=node.End(); it++){
        auto& value = (*it).second;
        if(value.IsMap()){
            array.append(toObject(value));
        }else if(value.IsSequence()){
            array.append(toArray(value));
        }else{
            array.append(toValue(value));
        }
    }
    return array;
}

static QJsonObject toObject(const Yaml::Node& node){
    QJsonObject obj;
    for(auto it=node.Begin(); it!=node.End(); it++){
        QString key = QString::fromStdString((*it).first);
        auto& value = (*it).second;
        if(value.IsMap()){
            obj[key] = toObject(value);
        }else if(value.IsSequence()){
            obj[key] = toArray(value);
        }else{
            obj[key] = toValue(value);
        }
    }
    return obj;
}

static QJsonValue toValue( const Yaml::Node& node){
    if(node.IsNone()){
        return "";
    }
//    if()


    if(node.IsScalar()){
        // TODO: 这个需要解析成不同的数据类型, 先不做这个了，麦格雷
        auto value = QString::fromStdString( node.As<std::string>());
        return value;
    }
    return {};
}


static QJsonObject toJsonObject(const QString &content, bool& ok)
{
    ok = true;
    Yaml::Node root;

    try {
        Yaml::Parse(root, content.toStdString());
    } catch (Yaml::ParsingException e) {
         IConfigAbort::abortConfigurationCovertYamlFailError(e.what(), $ISourceLocation);
    }
    if(root.IsMap()){
        return toObject(root);
    }

    ok = false;
    return {};
}

QJsonValue IContextYamlProfileTask::config()
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

QJsonValue IContextYamlProfileTask::parseYamlFile(const QString &path, bool& ok)
{
    QJsonObject obj;
    QString content = IFileUtil::readFileAsString(path, ok);
    if(!ok){
        IConfigAbort::abortConfigurationResolveJsonError($ISourceLocation);
    }

    obj = toJsonObject(content, ok);
    if(!ok){
        IConfigAbort::abortConfigurationResolveJsonError(path, $ISourceLocation);
    }
    return obj;
}

$PackageWebCoreEnd

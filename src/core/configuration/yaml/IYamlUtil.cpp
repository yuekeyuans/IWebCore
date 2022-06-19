#include "IYamlUtil.h"

#include "Yaml.hpp"
#include "base/IToeUtil.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

namespace IYamlHelper{
    QJsonArray toArray(const Yaml::Node& node);
    QJsonObject toObject(const Yaml::Node& node);
    QJsonValue toValue(const Yaml::Node& node);
}

QJsonObject IYamlUtil::toJsonObject(const QString &content, bool* ok)
{
    IToeUtil::setOk(ok, true);
    Yaml::Node root;

    try {
        Yaml::Parse(root, content.toStdString());
    } catch (Yaml::ParsingException e) {
        IToeUtil::setOk(ok, false);
        IAssertInfo info;
        info.reason = e.what();
        $GlobalAssert->fatal(IGlobalAssert::ConfigurationCovertYamlFailError, info);    // actually, it need not ok, but for compat, write here for future.
    }
    if(root.IsMap()){
        return IYamlHelper::toObject(root);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QJsonArray IYamlHelper::toArray(const Yaml::Node& node){
    QJsonArray array;
    for(auto it=node.Begin(); it!=node.End(); it++){
        auto& value = (*it).second;
        if(value.IsMap()){
            array.append(IYamlHelper::toObject(value));
        }else if(value.IsSequence()){
            array.append(IYamlHelper::toArray(value));
        }else{
            array.append(IYamlHelper::toValue(value));
        }
    }
    return array;
}

QJsonObject IYamlHelper::toObject(const Yaml::Node& node){
    QJsonObject obj;
    for(auto it=node.Begin(); it!=node.End(); it++){
        QString key = QString::fromStdString((*it).first);
        auto& value = (*it).second;
        if(value.IsMap()){
            obj[key] = IYamlHelper::toObject(value);
        }else if(value.IsSequence()){
            obj[key] = IYamlHelper::toArray(value);
        }else{
            obj[key] = IYamlHelper::toValue(value);
        }
    }
    return obj;
}

QJsonValue IYamlHelper::toValue( const Yaml::Node& node){
    if(node.IsNone()){
        return "";
    }
    if(node.IsScalar()){
        // TODO: 这个需要解析成不同的数据类型, 先不做这个了，麦格雷
        auto value = QString::fromStdString( node.As<std::string>());
        return value;
    }
    return {};
}


$PackageWebCoreEnd

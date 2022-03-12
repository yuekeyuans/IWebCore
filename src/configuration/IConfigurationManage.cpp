#include "IConfigurationManage.h"

#include "assertion/IAssertPreProcessor.h"

#include "base/IJsonUtil.h"
#include "base/IMetaUtil.h"
#include "base/IConstantUtil.h"
#include "base/IConvertUtil.h"

$PackageWebCoreBegin

const char SystemConfigurationGroup[] = "System";
const char ApplicationConfigurationGroup[] = "Application";
//const char UserConfigurationGroup[] = "User";

struct ConfigurationBean{
    QString type;
    QString name;
    QString path;
    bool optional {false};
    QMetaType::Type typeId {QMetaType::UnknownType};
    QString group {ApplicationConfigurationGroup};
};

namespace IConfigurationManageHelper {
    bool checkConfigValueType(QMetaType::Type type);
    QVector<ConfigurationBean> generateConfigurationBean(const QMap<QString, QString>&clsInfo, const QVector<QMetaProperty> &props);

    QJsonValue getMergeValue(const QString key, const QJsonObject &dest, const QJsonObject &source);
    QJsonObject mergeJsonObject(const QJsonObject &dest, const QJsonObject &source);
    QJsonObject addJsonValue(const QJsonObject& root, const QString& path, const QJsonValue value);
}

void IConfigurationManage::registerConfiguration(QString group, const QJsonObject& obj)
{
    auto inst = instance();
    if(inst->m_configs.contains(group)){
        auto originValue = inst->m_configs[group];
        inst->m_configs[group] = IConfigurationManageHelper::mergeJsonObject(originValue, obj);
    }else{
        inst->m_configs[group] = obj;
    }
}

void IConfigurationManage::setSystemValue(const QString &path, const QJsonValue &value)
{
    return setValue(path, value, SystemConfigurationGroup);
}

void IConfigurationManage::setApplicationValue(const QString &path, const QJsonValue &value)
{
    return setValue(path, value, ApplicationConfigurationGroup);
}

bool IConfigurationManage::getBoolValue(const QString &path, bool *ok, const QString &group)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto value = getValue(path, &convertOk, group);
    if(convertOk){
        return IConvertUtil::toBool(value, ok);
    }

    IToeUtil::setOkAnd(ok, convertOk);
    return false;
}

int IConfigurationManage::getIntValue(const QString &path, bool *ok, const QString &group)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto value = getValue(path, &convertOk, group);
    if(convertOk){
        return IConvertUtil::toInt(value, ok);
    }

    IToeUtil::setOkAnd(ok, convertOk);
    return 0;
}

double IConfigurationManage::getDoubleValue(const QString &path, bool *ok, const QString &group)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;
    auto value = getValue(path, &convertOk, group);
    if(convertOk){
        return IConvertUtil::toDouble(value, ok);
    }

    IToeUtil::setOkAnd(ok, convertOk);
    return 0;
}

QString IConfigurationManage::getStringValue(const QString &path, bool *ok, const QString &group)
{
    IToeUtil::setOk(ok, true);
    bool convertOk;

    auto value = getValue(path, &convertOk, group);
    if(!convertOk || value.isArray() || value.isObject() || value.isNull() || value.isUndefined()){
        IToeUtil::setOk(ok, false);
        return "";
    }
    IToeUtil::setOkAnd(ok, convertOk);

    if(value.isDouble()){
        return QString::number(value.toDouble());
    }else if(value.isBool()){
        return IConvertUtil::toString(value.toBool());
    }else if(value.isString()){
        return value.toString();
    }
    IToeUtil::setOk(ok, false);
    return "";
}

void IConfigurationManage::setValue(const QString& path, const QJsonValue& value, const QString& group)
{
    auto inst = instance();
    auto obj = inst->m_configs[group];
    inst->m_configs[group] = IConfigurationManageHelper::addJsonValue(obj, path, value);
}

QJsonValue IConfigurationManage::getSystemValue(const QString &path, bool*ok)
{
    return getValue(path, ok, SystemConfigurationGroup);
}

QJsonValue IConfigurationManage::getApplicationValue(const QString &path, bool *ok)
{
    return getValue(path, ok, ApplicationConfigurationGroup);
}

QJsonValue IConfigurationManage::getValue(const QString &path, bool* ok, const QString &group)
{
    IToeUtil::setOk(ok, true);

    auto inst = instance();
    if(!inst->m_isInited){
        $AssertWarning(configuration_may_not_initialized)
    }

    if(!inst->m_configs.contains(group)){
        IToeUtil::setOk(ok, false);
        return {};
    }

    bool convertOk;
    auto value = IJsonUtil::getJsonValue(inst->m_configs[group], path, &convertOk);
    if(convertOk){
        return value;
    }

    IToeUtil::setOk(ok, convertOk);
    return {};
}

QString IConfigurationManage::getBanner()
{
    auto inst = instance();
    auto value = IJsonUtil::getJsonValue(inst->m_configs[SystemConfigurationGroup], "banner");
    return value.toString();
}

void IConfigurationManage::getConfigBean(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaProperty> &props, bool *ok)
{
    IToeUtil::setOk(ok, true);
    auto inst = instance();
    if(!inst->m_isInited){
        $AssertWarning(configuration_may_not_initialized)
    }

    auto configBeans = IConfigurationManageHelper::generateConfigurationBean(clsInfo, props);
    for(auto it = configBeans.begin(); it != configBeans.end(); it++){

        if(!inst->m_configs.contains(it->group)){
            IToeUtil::setOk(ok, false);
            return;
//            QString info = "current configuration does not contains config group : " + it->group;
//            qWarning() << info;
//            continue;
        }

        bool convertOk;
        auto value = IJsonUtil::getJsonValue(inst->m_configs[it->group], it->path, &convertOk);
        if(!convertOk){
            QString info = "current path do not have configuration : path :" + it->path;
            qWarning() << info;
            continue;
        }

        QVariant val = IConvertUtil::toVariant(value, it->typeId, &convertOk);
        if(!convertOk){
            QString info = "current path do not have configuration : path :" + it->path;
            qWarning() << info;
            continue;
        }

        auto property = IMetaUtil::getMetaPropertyByName(props, it->name);
        IMetaUtil::writeProperty(property, handler, val);
    }
}


bool IConfigurationManageHelper::checkConfigValueType(QMetaType::Type type){
    static const QList<QMetaType::Type> validTypes = {
        QMetaType::Bool,
        QMetaType::QString,
        QMetaType::QStringList, // support QStringList.
        QMetaType::Short, QMetaType::UShort,
        QMetaType::Int, QMetaType::UInt,
        QMetaType::Long, QMetaType::ULong,
        QMetaType::LongLong, QMetaType::ULongLong,
        QMetaType::Double, QMetaType::Float,
        QMetaType::QDate, QMetaType::QTime, QMetaType::QDateTime,   // support time
    };
    auto result = validTypes.contains(type);
    if(!result){
        QString info = QString("current field type is not supported, please change to a valid type. \n"
                       "type:") + QMetaType::typeName(type);
        qFatal(info.toUtf8());
    }
    return result;
}

QVector<ConfigurationBean> IConfigurationManageHelper::generateConfigurationBean(const QMap<QString, QString>&clsInfo, const QVector<QMetaProperty> &props){
    static const char* const Config_Prefix = "iwebConfigWire__";
    QVector<ConfigurationBean> configBeans;

    const auto& keys = clsInfo.keys();
    for(auto key : keys){
        if(key.startsWith(Config_Prefix) && key.endsWith("_name")){
            ConfigurationBean bean;
            bean.name = clsInfo[key];
            configBeans.append(bean);
        }
    }

    for(auto& bean : configBeans){
        const QString prefix = QString(Config_Prefix).append(bean.name);
        auto groupName = prefix + "_group";
        auto pathName  = prefix + "_path";
        auto optional  = prefix + "_option";
        if(clsInfo.contains(groupName)){
            bean.group = clsInfo[groupName];
        }
        if(clsInfo.contains(pathName)){
            bean.path = clsInfo[pathName];
        }
        if(clsInfo.contains(optional)){
            bean.optional = true;
        }
        auto prop = IMetaUtil::getMetaPropertyByName(props, bean.name);
        bean.type = prop.typeName();
        bean.typeId = QMetaType::Type(prop.type());
        IConfigurationManageHelper::checkConfigValueType(bean.typeId);
    }
    return configBeans;
}

QJsonValue IConfigurationManageHelper::getMergeValue(const QString key, const QJsonObject &dest, const QJsonObject &source)
{
    QJsonValue destValue = dest[key];
    QJsonValue srcValue = source[key];
    if(destValue.isObject() && source[key].isObject()){             // object 合并
        QJsonObject destObj = destValue.toObject();
        return mergeJsonObject(destObj, srcValue.toObject());
    }else if(destValue.isArray() && source[key].isArray()){         // array 合并
        QJsonArray destArray = destValue.toArray();
        QJsonArray sourceArray = srcValue.toArray();
        for(QJsonValue val : sourceArray){
            destArray.append(val);
        }
        return destArray;
    } else if((destValue.isObject() || destValue.isArray()          // 其中有一方是 obj 或 array, 但另一方类型不同
                || srcValue.isArray() || srcValue.isObject())){
        $AssertFatal(merge_json_config_value_error)
    }else{                                                          // 都是普通值类型， 新的替换旧的
        return source[key];
    }
    return destValue;
}

QJsonObject IConfigurationManageHelper::mergeJsonObject(const QJsonObject &dest, const QJsonObject &source)
{
    QJsonObject ret = dest;
    auto keys = source.keys();
    for(auto key : keys){
        if(dest.contains(key)){
            ret[key] = getMergeValue(key, dest, source);
        }else{
            ret[key] = source[key];
        }
    }
    return ret;
}

QJsonObject IConfigurationManageHelper::addJsonValue(const QJsonObject& root, const QString& path, const QJsonValue value)
{
    auto pieces = path.split('.');
    if(pieces.isEmpty() || pieces.first().startsWith("_")){
        qFatal("error");    // NOTE: 这个是一个错误，之后在 fatalAssert;
    }

    QJsonValue curValue = value;
    for(auto it=pieces.crbegin(); it!=pieces.crend(); it++){
        if(it->startsWith('_')){   // 不判断第几个，只说明这是一个 index.
            QJsonArray array;
            array.push_back(curValue);
            curValue = array;
        }else{
            QJsonObject obj;
            obj[*it] = curValue;
            curValue = obj;
        }
    }

    return IConfigurationManageHelper::mergeJsonObject(root, curValue.toObject());
};


$PackageWebCoreEnd

#include "IContextManage.h"

#include "core/base/IJsonUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/base/IConstantUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IToeUtil.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

const char SystemConfigurationGroup[] = "System";
const char ApplicationConfigurationGroup[] = "Application";

struct ConfigurationBean{
    QString type;
    QString name;
    QString path;
    bool optional {false};
    QMetaType::Type typeId {QMetaType::UnknownType};
    QString group {ApplicationConfigurationGroup};
};

namespace IContextManageHelper {
    bool checkConfigValueType(QMetaType::Type type);
    QVector<ConfigurationBean> generateConfigurationBean(const QMap<QString, QString>&clsInfo, const QVector<QMetaProperty> &props);

    QJsonValue getMergeValue(const QString key, const QJsonObject &dest, const QJsonObject &source);
    void mergeJsonObject(QJsonObject &dest, const QJsonObject &source);
    void addJsonValue(QJsonObject& dest, const QJsonValue& from, const QString& path="");

    QJsonValue getRemovedValue(QJsonValue val, QStringList pieces);
    QJsonObject removeJsonValue(QJsonObject& dest, const QString& path);
}

IContextManage::IContextManage()
{
//        setSystemConfig("CONFIG_TEST_PYTHON_INPUT_PATH", ":/test/python/");
//        setSystemConfig("CONFIG_TEST_PYTHON_OUTPUT_PATH", "./.python");
}

QJsonValue IContextManage::getSystemConfig(const QString &path, bool*ok)
{
    return getConfig(path, ok, SystemConfigurationGroup);
}

QJsonValue IContextManage::getApplicationConfig(const QString &path, bool *ok)
{
    return getConfig(path, ok, ApplicationConfigurationGroup);
}

bool IContextManage::getSystemConfigAsBool(const QString &path, bool *ok)
{

}

//bool IContextManage::getConfigAsBool(const QString &path, bool *ok, const QString &group)
//{
//    IToeUtil::setOk(ok, true);
//    bool convertOk;
//    auto value = getConfig(path, &convertOk, group);
//    if(convertOk){
//        return IConvertUtil::toBool(value, ok);
//    }

//    IToeUtil::setOkAnd(ok, convertOk);
//    return false;
//}

//int IContextManage::getConfigAsInt(const QString &path, bool *ok, const QString &group)
//{
//    IToeUtil::setOk(ok, true);
//    bool convertOk;
//    auto value = getConfig(path, &convertOk, group);
//    if(convertOk){
//        return IConvertUtil::toInt(value, ok);
//    }

//    IToeUtil::setOkAnd(ok, convertOk);
//    return 0;
//}

//double IContextManage::getConfigAsDouble(const QString &path, bool *ok, const QString &group)
//{
//    IToeUtil::setOk(ok, true);
//    bool convertOk;
//    auto value = getConfig(path, &convertOk, group);
//    if(convertOk){
//        return IConvertUtil::toDouble(value, ok);
//    }

//    IToeUtil::setOkAnd(ok, convertOk);
//    return 0;
//}

//QString IContextManage::getConfigAsString(const QString &path, bool *ok, const QString &group)
//{
//    IToeUtil::setOk(ok, true);
//    bool convertOk;

//    auto value = getConfig(path, &convertOk, group);
//    if(!convertOk || value.isArray() || value.isObject() || value.isNull() || value.isUndefined()){
//        IToeUtil::setOk(ok, false);
//        return "";
//    }
//    IToeUtil::setOkAnd(ok, convertOk);

//    if(value.isDouble()){
//        return QString::number(value.toDouble());
//    }else if(value.isBool()){
//        return IConvertUtil::toString(value.toBool());
//    }else if(value.isString()){
//        return value.toString();
//    }
//    IToeUtil::setOk(ok, false);
//    return "";
//}

QJsonValue IContextManage::getConfig(const QString &path, bool* ok, const QString &group)
{
    IToeUtil::setOk(ok, true);

    auto inst = instance();
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


void IContextManage::addConfig(const QJsonValue& value, const QString& group, const QString& path)
{
    auto inst = instance();
    auto& obj = inst->m_configs[group];
    IContextManageHelper::addJsonValue(obj, value, path);
}

void IContextManage::removeConfig(const QString &group, const QString &path)
{
    auto inst = instance();
    auto& obj = inst->m_configs[group];
    inst->m_configs[group] = IContextManageHelper::removeJsonValue(obj, path);
}

void IContextManage::getConfigBean(void *handler, const QMap<QString, QString> &clsInfo, const QVector<QMetaProperty> &props, bool *ok)
{
    IToeUtil::setOk(ok, true);
    auto inst = instance();
    auto configBeans = IContextManageHelper::generateConfigurationBean(clsInfo, props);
    for(auto it = configBeans.begin(); it != configBeans.end(); it++){

        if(!inst->m_configs.contains(it->group)){
            IToeUtil::setOk(ok, false);
            return;
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


bool IContextManageHelper::checkConfigValueType(QMetaType::Type type){
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

QVector<ConfigurationBean> IContextManageHelper::generateConfigurationBean(const QMap<QString, QString>&clsInfo, const QVector<QMetaProperty> &props){
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
        IContextManageHelper::checkConfigValueType(bean.typeId);
    }
    return configBeans;
}

QJsonValue IContextManageHelper::getMergeValue(const QString key, const QJsonObject &dest, const QJsonObject &source)
{
    QJsonValue destValue = dest[key];
    QJsonValue srcValue = source[key];
    if(destValue.isObject() && source[key].isObject()){             // object 合并
        QJsonObject destObj = destValue.toObject();
        mergeJsonObject(destObj, srcValue.toObject());
        return destObj;
    }else if(destValue.isArray() && source[key].isArray()){         // array 合并
        QJsonArray destArray = destValue.toArray();
        QJsonArray sourceArray = srcValue.toArray();
        for(QJsonValue val : sourceArray){
            destArray.append(val);
        }
        return destArray;
    } else if((destValue.isObject() || destValue.isArray()          // 其中有一方是 obj 或 array, 但另一方类型不同
                || srcValue.isArray() || srcValue.isObject())){
        $GlobalAssert->fatal(IGlobalAssert::ConfigurationMergeJsonValueError);
    }else{                                                          // 都是普通值类型， 新的替换旧的
        return source[key];
    }
    return destValue;
}

void IContextManageHelper::mergeJsonObject(QJsonObject &dest, const QJsonObject &source)
{
    auto keys = source.keys();
    for(auto key : keys){
        if(dest.contains(key)){
            dest[key] = getMergeValue(key, dest, source);
        }else{
            dest[key] = source[key];
        }
    }
}

void IContextManageHelper::addJsonValue(QJsonObject& root, const QJsonValue& value, const QString& path)
{
    QJsonValue curValue = value;

    if(!path.isEmpty()){
        auto pieces = path.split('.');
        if(pieces.isEmpty() || pieces.first().startsWith("_")){
            $GlobalAssert->fatal("ContextAddPathInvalid");
        }

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
    }

    return IContextManageHelper::mergeJsonObject(root, curValue.toObject());
}


QJsonValue IContextManageHelper::getRemovedValue(QJsonValue val, QStringList pieces)
{
    if(pieces.isEmpty()){
        qFatal("this should not appear");
        return {};
    }

    auto piece = pieces.first();
    pieces.pop_front();

    if(piece.startsWith("_")){
        if(!val.isArray()){
            $GlobalAssert->fatal("ContextResolvePathInvalid");
            return val;
        }
        bool ok;
        auto index = IConvertUtil::toInt(piece.remove(0, 1), &ok);
        if(!ok){
            $GlobalAssert->fatal("ContextResolvePathInvalid");
        }
        if(val.toArray().size() <= index){
            $GlobalAssert->fatal("ContextResolvePathInvalid");
        }

        auto array = val.toArray();
        if(pieces.isEmpty()){
            array.removeAt(index);
        }else{
            array[index] = getRemovedValue(array[index], pieces);
        }
        return array;

    }else{
        if(!val.isObject()){
            $GlobalAssert->fatal("ContextResolvePathInvalid");
        }
        auto obj = val.toObject();
        if(pieces.isEmpty()){
            obj.remove(piece);
        }else{
            obj[piece] = getRemovedValue(obj[piece], pieces);
        }
    }
}

// 删除如何设置
QJsonObject IContextManageHelper::removeJsonValue(QJsonObject &dest, const QString &path)
{
    auto pieces = path.split('.');
    if(pieces.isEmpty() || pieces.first().startsWith("_")){
        $GlobalAssert->fatal("ContextRemovePathInvalid");
    }

    return IContextManageHelper::getRemovedValue(dest, pieces).toObject();
}


$PackageWebCoreEnd

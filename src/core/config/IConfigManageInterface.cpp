#include "IConfigManageInterface.h"
#include "core/base/IToeUtil.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

namespace IConfigUnitHelper
{
    static void validatePath(const QStringList& args){
        if(args.contains("@^") || args.contains("@$")){
            $GlobalAssert->warn("JsonMergeWarnWithArray");
        }
    }

    static QJsonValue buildJsonByPath(const QStringList& args, QJsonValue value)
    {
        QJsonValue val = value;
        for(auto it = args.rbegin(); it != args.rend(); it++){
            if(*it == "@^" || *it == "@$"){
                QJsonArray array;
                array.append(val);
                val = array;
            }else{
                QJsonObject obj;
                obj[*it] = val;
                val = obj;
            }
        }
        return val;
    }

    static QJsonValue mergeJsonObject(const QJsonValue &target, const QJsonValue &source, QStringList args)
    {
        const auto& arg = args.first();
        if(arg == "@^" || arg == "@$"){
            if(!target.isArray() || !source.isArray()){
                $GlobalAssert->fatal("JsonArrayMergeMismatch");
            }

            QJsonArray array = target.toArray();
            if(arg == "@^"){
                array.push_front(source.toArray().first());
            }else{
                array.push_back(source.toArray().first());
            }
            return array;
        }else{
            if(!target.isObject() || !source.isObject()){
                $GlobalAssert->fatal("JsonObjectMergeMismatch");
            }

            QJsonObject obj = target.toObject();
            if(!obj.contains(arg) || args.length() == 1){
                obj[arg] = source[arg];
            }else{
                obj[arg] = mergeJsonObject(obj[arg], source[arg], args.mid(1));
            }
            return obj;
        }
    }

    QJsonObject addToJsonObject(const QJsonObject &obj, const QString &path, QJsonValue value)
    {
        QStringList args = path.split(".");
        validatePath(args);
        assert(args.length() != 0);
        assert(args.first() != "@^" && args.first() != "@$");

        auto val = buildJsonByPath(args, value);
        return mergeJsonObject(obj, val, args).toObject();
    }

    QJsonValue getJsonValue(const QJsonObject &obj, const QString &path, bool *ok)
    {
        QStringList args = path.split(".");
        QJsonValue value = obj;
        for(const auto& arg : args){
            if(!value.isObject()){
                $GlobalAssert->warn("JsonFetchNotSupportArrary");
                IToeUtil::setOk(ok, false);
                return {};
            }
            QJsonObject temp = value.toObject();
            if(!temp.contains(arg)){
                IToeUtil::setOk(ok, false);
                return {};
            }
            value = temp[arg];
        }
        IToeUtil::setOk(ok, true);
        return value;
    }
}

void IConfigManageInterface::addConfig(const QJsonValue &value, const QString &path)
{
    if(path.trimmed().isEmpty()){
        if(!value.isObject()){
            $GlobalAssert->fatal("ContextMergeError");
        }
        QJsonObject obj = value.toObject();
        auto names = obj.keys();
        for(const auto& name : names){
            m_configs[name] = obj[name];
        }
    }

    m_configs = IConfigUnitHelper::addToJsonObject(m_configs, path, value);
}

QJsonValue IConfigManageInterface::getConfig(const QString &path, bool *ok)
{
    return IConfigUnitHelper::getJsonValue(m_configs, path, ok);
}

bool IConfigManageInterface::getConfigAsBool(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(*ok){
        return IConvertUtil::toBool(value, ok);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

int IConfigManageInterface::getConfigAsInt(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(*ok){
        return IConvertUtil::toInt(value, ok);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

double IConfigManageInterface::getConfigAsDouble(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(*ok){
        return IConvertUtil::toDouble(value, ok);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

// NOTE: 这个是对的，在具体的判断过程中，不应该把 Object array 等对象判断成为 String,
static QString jsonValueToString(const QJsonValue& value, bool* ok)
{
    if(value.isNull() || value.isUndefined()){
        IToeUtil::setOk(ok, false);
        return {};
    }

    if(value.isArray() || value.isObject() ){
        IToeUtil::setOk(ok, false);
        return IConvertUtil::toString(value, ok);
    }

    IToeUtil::setOk(ok, true);
    if(value.isDouble()){
        return QString::number(value.toDouble());
    }else if(value.isBool()){
        return IConvertUtil::toString(value.toBool());
    }else if(value.isString()){
        return value.toString();
    }

    IToeUtil::setOk(ok, false);
    return {};
}

QString IConfigManageInterface::getConfigAsString(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(*ok){
        return jsonValueToString(value, ok);
    }

    IToeUtil::setOk(ok, false);
    return {};
}

$PackageWebCoreEnd


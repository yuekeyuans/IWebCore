#include "IConfigManageInterface.h"
#include "core/util/IToeUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/abort/IAbortInterface.h"
#include "core/config/IConfigAbort.h"

$PackageWebCoreBegin

namespace IConfigUnitHelper
{
    static void validatePath(const QStringList& args){
        if(args.isEmpty()){
            IConfigAbort::abortContextAddPathInvalid($ISourceLocation);
        }
        if(args.contains("@^") && !args.endsWith("@^")){
            IConfigAbort::abortJsonMergeFatalWithArray($ISourceLocation);
        }
        if(args.contains("@$") && !args.endsWith("@$")){
            IConfigAbort::abortJsonMergeFatalWithArray($ISourceLocation);
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

    static QJsonObject mergeJsonObject(const QJsonObject& obj, const QJsonObject& obj2)
    {
        QJsonObject ret = obj;
        auto keys = obj2.keys();
        for(const auto& key : keys){
            if(!ret.contains(key)){
                ret[key] = obj2[key];
                continue;
            }

            if(obj[key].isObject() || obj2[key].isObject()){
                if(obj[key].isObject() && obj2[key].isObject()){
                    ret[key] = mergeJsonObject(obj[key].toObject(), obj2[key].toObject());
                }else{
                    IConfigAbort::abortContextMergeError($ISourceLocation);
                }
            }else if(obj[key].isArray() || obj2[key].isArray()){
                if(obj[key].isArray() && obj2[key].isArray()){
                    auto array = ret[key].toArray();
                    array.append(obj2[key].toArray());
                    ret[key] = array;
                }else{
                    IConfigAbort::abortContextMergeError($ISourceLocation);
                }
            }else{
                ret[key] = obj2[key];   // 重写内容
            }
        }

        return ret;
    }

    static QJsonValue mergeJsonObject(const QJsonValue &target, const QJsonValue &source, QStringList args)
    {
        const auto& arg = args.first();
        if(arg == "@^" || arg == "@$"){
            if(!target.isArray() || !source.isArray()){
                IConfigAbort::abortJsonArrayMergeMismatch($ISourceLocation);
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
                IConfigAbort::abortJsonArrayMergeMismatch($ISourceLocation);
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

        auto val = buildJsonByPath(args, value);
        return mergeJsonObject(obj, val, args).toObject();
    }

    QJsonValue getJsonValue(const QJsonObject &obj, const QString &path, bool& ok)
    {
        QStringList args = path.split(".");
        QJsonValue value = obj;
        for(const auto& arg : args){
            if(!value.isObject()){
                IConfigAbort::abortJsonFetchNotSupportArrary($ISourceLocation);
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

void IConfigManageInterface::addConfig(const IJson &value, const QString &path)
{
    if(path.trimmed().isEmpty()){
        if(!value.is_object()){
            IConfigAbort::abortContextMergeError($ISourceLocation);
        }
        IJson::json_pointer pointer(path.toStdString());
        IJson obj = IJson::object();
        obj[pointer] = value;
        m_configs.merge_patch(obj);
//        m_configs = IConfigUnitHelper::mergeJsonObject(m_configs, value.toObject());
    }else{
        m_configs.merge_patch(value);
//        m_configs = IConfigUnitHelper::addToJsonObject(m_configs, path, value);
    }
}

IJson IConfigManageInterface::getConfig(const QString &path)
{
    return m_configs.value(IJson::json_pointer(path.toStdString()), nullptr);
}

bool IConfigManageInterface::getConfigAsBool(const QString &path, bool& ok)
{
    auto value = getConfig(path);
    if(value.is_null() || !value.is_boolean()){
        ok = false;
        return false;
    }
    ok = true;
    return value.get<bool>();
}

IResult<bool> IConfigManageInterface::getConfigAsBool(const QString &path)
{
    bool ok;
    auto value = getConfigAsBool(path, ok);
    if(ok){
        return value;
    }
    return std::nullopt;
}

int IConfigManageInterface::getConfigAsInt(const QString &path, bool& ok)
{
    auto value = getConfig(path);
    if(value.is_null() || !value.is_number_integer()){
        ok = false;
        return {};
    }

    return value.get<int>();
}

IResult<int> IConfigManageInterface::getConfigAsInt(const QString &path)
{
    bool ok;
    auto value = getConfigAsInt(path, ok);
    if(ok){
        return value;
    }
    return std::nullopt;
}

double IConfigManageInterface::getConfigAsDouble(const QString &path, bool& ok)
{
    auto value = getConfig(path);
    if(value.is_null() || !value.is_number()){
        ok = false;
        return {};
    }

    return value.get<double>();
}

IResult<double> IConfigManageInterface::getConfigAsDouble(const QString &path)
{
    bool ok;
    auto value = getConfigAsDouble(path, ok);
    if(ok){
        return value;
    }
    return std::nullopt;
}

// NOTE: 这个是对的，在具体的判断过程中，不应该把 Object array 等对象判断成为 String,
static QString jsonValueToString(const QJsonValue& value, bool& ok)
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

QString IConfigManageInterface::getConfigAsString(const QString &path, bool& ok)
{
    auto value = getConfig(path);
    if(value.is_null() || !value.is_string()){
        ok = false;
        return {};
    }
    return QString::fromStdString(value.get<std::string>());
}

IResult<QString> IConfigManageInterface::getConfigAsString(const QString &path)
{
    bool ok;
    auto value = getConfigAsString(path, ok);
    if(ok){
        return value;
    }
    return std::nullopt;
}

$PackageWebCoreEnd


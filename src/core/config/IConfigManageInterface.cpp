#include "IConfigManageInterface.h"
#include "core/util/IToeUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/abort/IAbortInterface.h"
#include "core/config/IConfigAbort.h"

$PackageWebCoreBegin

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
    return getConfig(path.toStdString());
}

IJson IConfigManageInterface::getConfig(const std::string &path)
{
    IJson::json_pointer p(path);
    if(m_configs.contains(p)){
        return m_configs[p];
    }
    return nullptr;
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


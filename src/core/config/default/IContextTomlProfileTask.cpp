#include "IContextTomlProfileTask.h"
#include "toml.hpp"
#include "core/base/IFileUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/config/IContextImport.h"

$PackageWebCoreBegin

double IContextTomlProfileTask::order() const
{
    return 99.0;
}

QJsonValue IContextTomlProfileTask::config()
{
    $ContextBool enableConfigFiles{"config.enableConfigFiles", false};
    if(!enableConfigFiles.isFound() || !enableConfigFiles){
        return {};
    }

    auto paths = getValidatedPaths();
    for(auto path : paths){
        bool ok;
        auto obj = parseToml(path, ok);
        if(ok){
            IProfileManage::instance()->addConfig(obj);
        }
    }

    return {};
}

static QDate tomlLocalDateToQDate(const toml::local_date& localDate) {
    return QDate(localDate.year, localDate.month, localDate.day);
}

static QDateTime tomlLocalDateTimeToQDateTime(const toml::local_datetime& localDateTime) {
    return QDateTime(QDate(localDateTime.date.year, localDateTime.date.month, localDateTime.date.month),
                     QTime(localDateTime.time.hour, localDateTime.time.minute, localDateTime.time.second));
}

static QTime tomlLocalTimeToQTime(const toml::local_time& localTime) {
    return QTime(localTime.hour, localTime.minute, localTime.second);
}

static QJsonValue tomlToJson(const toml::value& value) {

    if(value.is_boolean()){
        return value.as_boolean();
    }
    if(value.is_integer()){
        return value.as_integer();
    }
    if(value.is_floating()){
        return value.as_floating();
    }
    if(value.is_string()){
        return QString::fromStdString(value.as_string());
    }
    if(value.is_table()){
        QJsonObject ret;
        auto obj = value.as_table();
        for(const auto& [key, val] : obj){
            ret[QString::fromStdString(key)] = tomlToJson(val);
        }
        return ret;
    }
    if(value.is_array()){
        QJsonArray ret;
        auto array = value.as_array();
        for (const auto& element : array) {
            ret.append(tomlToJson(element));
        }
        return ret;
    }
    if(value.is_local_date()){
        return IConvertUtil::toString(tomlLocalDateToQDate(value.as_local_date()));
    }
    if(value.is_local_datetime()){
        return IConvertUtil::toString(tomlLocalDateTimeToQDateTime(value.as_local_datetime()));
    }
    if(value.is_local_time()){
        return IConvertUtil::toString(tomlLocalTimeToQTime(value.as_local_time()));
    }
    if(value.is_offset_datetime()){
        qFatal("not supported");
    }
    if(value.is_uninitialized()){
        return QJsonValue::Null;
    }
    return {};
}

static std::vector<char> toVector(std::string value)
{
    std::vector<char> ret(value.length());
    std::memcpy(ret.data(), value.c_str(), sizeof(char)*value.length());
    return ret;
}

QJsonValue IContextTomlProfileTask::parseToml(const QString &path, bool &ok)
{
    if(path.startsWith(":/")){
        QString content = IFileUtil::readFileAsString(path, ok);
        if(ok){
            auto vec = toVector(content.toStdString());
            auto value = toml::detail::parse(vec, path.toStdString());
            return tomlToJson(value);
        }
    }else{
        auto value = toml::parse(path.toStdString());
        return tomlToJson(value);
    }

    return {};
}

QStringList IContextTomlProfileTask::nameFilters() const
{
    return {"*.toml", "*.tml"};
}


$PackageWebCoreEnd

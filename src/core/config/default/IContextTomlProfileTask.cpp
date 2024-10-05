#include "IContextTomlProfileTask.h"
#include "toml.hpp"
#include "core/util/IFileUtil.h"
#include "core/config/IContextImport.h"
#include "core/config/IConfigAbort.h"

$PackageWebCoreBegin

double IContextTomlProfileTask::order() const
{
    return 99.0;
}

IJson IContextTomlProfileTask::config()
{
    $ContextBool enableConfigFiles{"/config/enableConfigFiles", false};
    if(!enableConfigFiles.value()){
        return nullptr;
    }

    auto paths = getFilteredPaths();
    for(auto path : paths){
        bool ok;
        auto obj = parseToml(path, ok);
        if(ok){
            IProfileManage::instance()->addConfig(obj);
        }
    }

    return nullptr;
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

static IJson tomlToJson(const toml::value& value) {

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
        return value.as_string();
    }
    if(value.is_table()){
        IJson ret = IJson::object();
        auto obj = value.as_table();
        for(const auto& [key, val] : obj){
            ret[key] = tomlToJson(val);
        }
        return ret;
    }
    if(value.is_array()){
        IJson ret = IJson::array();
        auto array = value.as_array();
        for (const auto& element : array) {
            ret.push_back(tomlToJson(element));
        }
        return ret;
    }

    if(value.is_uninitialized()){
        return nullptr;
    }
    return {};
}

static std::vector<char> toVector(std::string value)
{
    std::vector<char> ret(value.length());
    std::memcpy(ret.data(), value.c_str(), sizeof(char)*value.length());
    return ret;
}

IJson IContextTomlProfileTask::parseToml(const QString &path, bool &ok)
{
    if(path.startsWith(":/")){
        QString content = IFileUtil::readFileAsString(path, ok);
        if(ok){
            auto vec = toVector(content.toStdString());
            try{
                auto value = toml::detail::parse(vec, path.toStdString());
                return tomlToJson(value);
            } catch(...){
                QString tip = "File: " + path;
                IConfigAbort::abortConfigurationResolveTomlError(tip, $ISourceLocation);
            }
        }
    }

    try{
        auto value = toml::parse(path.toStdString());
        return tomlToJson(value);
    }catch(...){
        QString tip = "File: " + path;
        IConfigAbort::abortConfigurationResolveTomlError(tip, $ISourceLocation);
    }
    return nullptr;
}

QStringList IContextTomlProfileTask::nameFilters() const
{
    return {"*.toml", "*.tml"};
}

$PackageWebCoreEnd

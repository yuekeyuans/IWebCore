#include "IConfigUnit.h"
#include "core/base/IToeUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

void IConfigUnit::addConfig(const QJsonValue &value, const QString &path)
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

    m_configs = IJsonUtil::addToJsonObject(m_configs, path, value);
}

QJsonValue IConfigUnit::getConfig(const QString &path, bool *ok)
{
    return IJsonUtil::getJsonValue(m_configs, path, ok);
}

bool IConfigUnit::getConfigAsBool(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    if(ok){
        return value.toBool(ok);
    }
    return {};
}

int IConfigUnit::getConfigAsInt(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    return value.toInt();
}

double IConfigUnit::getConfigAsDouble(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    return value.toDouble();
}

QString IConfigUnit::getConfigAsString(const QString &path, bool *ok)
{
    auto value = getConfig(path, ok);
    return value.toString();
}

$PackageWebCoreEnd


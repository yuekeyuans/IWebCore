#include "IContextWritter.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

extern const char SystemConfigurationGroup[];
extern const char ApplicationConfigurationGroup[];

void IWebCore::IContextWritter::addSystemConfig(const QJsonValue &value, const QString &path)
{
    IContextManage::addConfig(value, SystemConfigurationGroup, path);
}

void IWebCore::IContextWritter::addApplicationConfig(const QJsonValue &value, const QString &path)
{
    IContextManage::addConfig(value, ApplicationConfigurationGroup, path);
}

$PackageWebCoreEnd

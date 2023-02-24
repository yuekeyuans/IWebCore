#include "IContextWritter.h"
#include "core/context/IContextManage.h"

$PackageWebCoreBegin

extern const char SystemContextGroup[];
extern const char ApplicationContextGroup[];

void IWebCore::IContextWritter::addSystemConfig(const QJsonValue &value, const QString &path)
{
    IContextManage::addConfig(value, SystemContextGroup, path);
}

void IWebCore::IContextWritter::addApplicationConfig(const QJsonValue &value, const QString &path)
{
    IContextManage::addConfig(value, ApplicationContextGroup, path);
}

$PackageWebCoreEnd

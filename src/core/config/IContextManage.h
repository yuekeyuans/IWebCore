#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/config/IConfigManageInterface.h"

$PackageWebCoreBegin

class ITaskManage;

class IContextManage final : public IConfigManageInterface
{
    $UseInstance(IContextManage)
private:
    IContextManage() = default;

public:
    template<typename T>
    static T getBean(const QString& path, bool*ok);
//    static void getConfigBean(void* handler, const QMap<QString, QString>& clsInfo, const QVector<QMetaProperty>&props, bool*ok);
};

template<typename T>
T IContextManage::getBean(const QString &path, bool* ok)
{
    return IContextManage::instance()->getBean<T>(path, ok);
}

$PackageWebCoreEnd

#define IContextManageInstance IContextManage::instance()

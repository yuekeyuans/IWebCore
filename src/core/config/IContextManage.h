#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/unit/IConfigUnit.h"

$PackageWebCoreBegin

class ITaskManage;

// TODO: 这里 Context 应该修改成 Config, 因为里面的内容全是 config 的， 没有context

class IContextManage final : public IConfigUnit
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
    auto value = getConfig(path, ok);
    if(*ok){
        return T::fromJson(value.toObject());
    }
    return {};
}

$PackageWebCoreEnd

#define IContextManageInstance IContextManage::instance()

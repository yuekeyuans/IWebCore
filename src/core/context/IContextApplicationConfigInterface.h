#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "IContextTaskInterface.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class IContextApplicationConfigInterface : public IContextTaskInterface<T, enabled>
{
public:
    IContextApplicationConfigInterface() = default;

public:
    virtual QJsonValue getApplicationConfig() = 0;

protected:
    virtual void task() final;

private:
    virtual QJsonValue getSystemConfig() final;
};

template<typename T, bool enabled>
void IContextApplicationConfigInterface<T, enabled>::task()
{
    QString path;
    const auto& map = IMetaUtil::getMetaClassInfoMap(T::staticMetaObject);
    if(map.contains("ABC")){
        qDebug() << "contains";
    }

    // TODO:
//    auto applicationConfig = getApplicationConfig();
//    if(!applicationConfig.isNull() && !applicationConfig.isUndefined()){
//        IContextManage::addApplicationConfig(applicationConfig, path);
//    }
}

template<typename T, bool enabled>
QJsonValue IContextApplicationConfigInterface<T, enabled>::getSystemConfig()
{
    return {};
}

$PackageWebCoreEnd

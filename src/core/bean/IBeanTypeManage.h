#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/unit/ISingletonUnit.h"
#include <functional>

$PackageWebCoreBegin

class IBeanTypeManage : public ISingletonUnit<IBeanTypeManage>
{
public:
    using ToJsonFun = std::function<QJsonValue(void*, bool*)>;
    using LoadJsonFun = std::function<bool(void*, const QJsonValue&)>;

public:
    IBeanTypeManage() = default;

public:
    void registerBeanId(int id);
    bool isBeanIdExist(int id);
    void registerToJsonFun(int id, ToJsonFun);
    void registerLoadJsonFun(int id, LoadJsonFun);
    ToJsonFun getToJsonFun(int id);
    LoadJsonFun getLoadJsonFun(int id);


private:
    QList<int> m_beanIds;
    QMap<int, ToJsonFun> m_toJsonMap;
    QMap<int, LoadJsonFun> m_loadJsonMap;
};

$PackageWebCoreEnd


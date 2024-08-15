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
    // TODO: 这里重新处理吧
    static void registerBeanType(const QString& typeName);
    static bool containBean(const QString& typeName);

public:
    void registerToJsonFun(int id, ToJsonFun);
    void registerLoadJsonFun(int id, LoadJsonFun);
    ToJsonFun getToJsonFun(int id);
    LoadJsonFun getLoadJsonFun(int id);


private:
    QStringList m_beanNames;
    QMap<int, ToJsonFun> m_toJsonMap;
    QMap<int, LoadJsonFun> m_loadJsonMap;
};

$PackageWebCoreEnd


#pragma once

#include <IWebCore>

class DataBean
{
    Q_GADGET
//    $UseConfig(DataBean)

    Q_INVOKABLE virtual void IWebPreRun_ResolveConfigField()
    {
        auto clsInfo = IMetaUtil::getMetaClassInfoMap(staticMetaObject);
        auto props = IMetaUtil::getMetaProperties(staticMetaObject);
        IConfigurationManage::getConfigBean(this, clsInfo, props);
    }

public:
    DataBean();

    $AutoWire(QString, name, name)
    $AutoWire(int, age, age);

    $AutoWireDeclare(QString, dbName, mysql.dbName);
    QString dbName = "unused";

    $AutoWire(QStringList, resPath, resPath)

    $AutoWire(QDate, birthDate);

    $AutoWire(bool, isValid);
};

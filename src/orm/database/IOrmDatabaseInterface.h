#pragma once

#include "base/IHeaderUtil.h"
#include "core/task/IInitializationTaskUnit.h"
#include "orm/IOrmManage.h"
#include "orm/database/IOrmDatabaseWare.h"
#include "orm/pp/IOrmPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmDatabaseInterface : public IOrmDatabaseWare, public IInitializationTaskUnit<T, enabled>
{
    $UseWare
public:
    IOrmDatabaseInterface() = default;
    virtual IOrmDataSource configDataSource() override = 0;
    virtual void registerEntities() override  =0;

    virtual QString taskFinishTip() final;
    virtual void task() final;
};

template<typename T, bool enabled>
QString IOrmDatabaseInterface<T, enabled>::taskFinishTip(){
    IOrmDataSource datasource = getDataSource();
    QString tip = "Database";
    if(!datasource.className().isEmpty()){
        tip.append(" At Class: ").append(datasource.className()).append(",");
    }
    if(!datasource.connectionName.isEmpty()){
        tip.append(" At Connection: ").append(datasource.connectionName).append(",");
    }
    if(!datasource.databaseName.isEmpty()){
        tip.append(" At Db: ").append(datasource.databaseName).append(",");
    }
    tip.append(" Opened");
    return tip;
}

template<typename T, bool enabled>
void IOrmDatabaseInterface<T, enabled>::task()
{
    openDatabase();

    auto name = this->getDatabase().connectionName();
    if(name.isEmpty() || name == "qt_sql_default_connection"){
        name = "default";
    }

    IOrmManage::registerDataBase(name, this);
}

$PackageWebCoreEnd

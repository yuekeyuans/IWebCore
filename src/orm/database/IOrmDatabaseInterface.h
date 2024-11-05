#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/task/ITaskManage.h"
#include "orm/IOrmManage.h"
#include "orm/IOrmTaskCatagory.h"
#include "orm/database/IOrmDatabaseWare.h"
#include "orm/pp/IOrmPreProcessor.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmDatabaseInterface : public IOrmDatabaseWare, public ITaskWareUnit<T, enabled>
{
    Q_DISABLE_COPY_MOVE(IOrmDatabaseInterface)
public:
    IOrmDatabaseInterface() = default;

public:
    virtual IOrmDataSource configDataSource() override = 0;
    virtual void registerEntities() override  =0;

public:
    virtual const QString& $catagory() const final;
    virtual double $order() const override;
    virtual void $task() final;

};

template<typename T, bool enabled>
const QString& IOrmDatabaseInterface<T, enabled>::$catagory() const
{
    return IOrmTaskCatagory::CATAGORY;
}

template<typename T, bool enabled>
double IOrmDatabaseInterface<T, enabled>::$order() const{
    return 49;
}


//template<typename T, bool enabled>
//QString IOrmDatabaseInterface<T, enabled>::taskFinishTip(){
//    IOrmDataSource datasource = getDataSource();
//    QString tip = "Database";
//    if(!datasource.className().isEmpty()){
//        tip.append(" At Class: ").append(datasource.className()).append(",");
//    }
//    if(!datasource.connectionName.isEmpty()){
//        tip.append(" At Connection: ").append(datasource.connectionName).append(",");
//    }
//    if(!datasource.databaseName.isEmpty()){
//        tip.append(" At Db: ").append(datasource.databaseName).append(",");
//    }
//    tip.append(" Opened");
//    return tip;
//}

template<typename T, bool enabled>
void IOrmDatabaseInterface<T, enabled>::$task()
{
    if constexpr (enabled){
        openDatabase();
        auto name = this->getDatabase().connectionName();
        if(name.isEmpty() || name == "qt_sql_default_connection"){
            name = "default";
        }
        IOrmManage::registerDataBase(name, this);
    }

}

$PackageWebCoreEnd

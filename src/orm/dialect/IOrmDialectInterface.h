#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "core/unit/ISingletonUnit.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmDialectInterface : public IOrmDialectWare, public ITaskWareUnit<T, enabled>, public ISingletonUnit<T>
{
public:
    IOrmDialectInterface() = default;
    virtual ~IOrmDialectInterface() = default;

public:
    virtual QString dialectType() override = 0;
    virtual QString getSqlType(const int typeId) override = 0;
    virtual QString getLimitString(int count) override = 0;
    virtual QString getLimitString(quint64 start, quint64 count) override = 0;

public:
    virtual double order() const{ return 2;}
    virtual QString name() const final { return "Sqlite Dialect";}
    virtual QString catagory() const final { return "Orm"; }
    virtual void task() final;
};

template<typename T, bool enabled>
void IOrmDialectInterface<T, enabled>::task() {
    auto inst = T::instance();
    IOrmManage::registerDialect(inst);
}

$PackageWebCoreEnd

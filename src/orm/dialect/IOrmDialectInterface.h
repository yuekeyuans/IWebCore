#pragma once

#include "base/IHeaderUtil.h"
#include "core/unit/IRegisterInstanceUnit.h"
#include "orm/dialect/IOrmDialectWare.h"
#include "orm/IOrmManage.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IOrmDialectInterface : public IOrmDialectWare, public IRegisterInstanceUnit<T, enabled>
{
    $UseWare
public:
    IOrmDialectInterface() = default;
    virtual ~IOrmDialectInterface() = default;

public:
    virtual QString dialectType() override = 0;
    virtual QString getSqlType(const int typeId) override = 0;
    virtual QString getLimitString(int count) override = 0;
    virtual QString getLimitString(quint64 start, quint64 count) override = 0;

private:
    virtual void registerToBase() override {
        auto inst = T::instance();
        IOrmManage::registerDialect(inst);
    };

private:
    friend class IRegisterInstanceUnit<T, enabled>;
};

$PackageWebCoreEnd

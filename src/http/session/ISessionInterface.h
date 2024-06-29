#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "http/session/ISessionWare.h"

$PackageWebCoreBegin

template<typename T, bool enabled=true>
class ISessionInterface : public ISessionWare, public ITaskWareUnit<T, enabled>
{
public:
    ISessionInterface() = default;

public:
    virtual QString name() const override;
    virtual double order() const override;
    virtual QString catagory() const final;
    virtual void registerToBase() final;
    virtual void task() final;
    virtual void registerSession() final;
};

namespace ISessionInterfaceProxy
{
    void registerSession(ISessionWare*);
}

template<typename T, bool enabled>
QString ISessionInterface<T, enabled>::name() const
{
    return IMetaUtil::getMetaClassName(T::staticMetaObject);
}

template<typename T, bool enabled>
double ISessionInterface<T, enabled>::order() const
{
    return 49;
}

template<typename T, bool enabled>
QString ISessionInterface<T, enabled>::catagory() const
{
    return "HttpController";
}

template<typename T, bool enabled>
void ISessionInterface<T, enabled>::registerToBase()
{
    // TODO:
}

template<typename T, bool enabled>
void ISessionInterface<T, enabled>::task ()
{
    static std::once_flag flag;
    std::call_once(flag, [&](){
        registerSession ();
    });
}

template<typename T, bool enabled>
void ISessionInterface<T, enabled>::registerSession ()
{
    ISessionInterfaceProxy::registerSession (T::instance());
}


$PackageWebCoreEnd

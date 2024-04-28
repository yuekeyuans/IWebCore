#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/task/unit/ITaskWareUnit.h"
#include "http/biscuits/IHttpStatus.h"
#include "http/invalid/IHttpInvalidWare.h"
#include "core/unit/ISingletonUnit.h"

$PackageWebCoreBegin

template<typename T, bool enabled = true>
class IHttpInvalidInterface : public IHttpInvalidWare //, public ITaskWareUnit<T, enabled>
{
public:
    IHttpInvalidInterface(IHttpStatusCode code, const QString& description="");

protected:
    virtual QString name() const final;
    virtual QString catagory() const final;
    virtual void task() final;
};

template<typename T, bool enabled>
IHttpInvalidInterface<T, enabled>::IHttpInvalidInterface(IHttpStatusCode status, const QString& description)
    : IHttpInvalidWare(status, IMetaUtil::getBareTypeName<T>(), description)
{
}

template<typename T, bool enabled>
QString IHttpInvalidInterface<T, enabled>::name() const
{
    return IMetaUtil::getBareTypeName<T>();
}

template<typename T, bool enabled>
QString IHttpInvalidInterface<T, enabled>::catagory() const
{
    return "HttpController";
}

template<typename T, bool enabled>
void IHttpInvalidInterface<T, enabled>::task()
{
    qDebug() << typeid(T).name();
}

$PackageWebCoreEnd

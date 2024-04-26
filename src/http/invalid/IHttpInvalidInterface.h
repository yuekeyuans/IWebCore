#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "http/biscuits/IHttpStatus.h"

$PackageWebCoreBegin

struct IHttpInvalidWare
{
public:
    IHttpInvalidWare() = default;
    IHttpInvalidWare(IHttpStatusCode status, const QString& name_, const QString& description_="")
        :status(status), name(name_), description(description_)
    {
        invalid = !name.isEmpty();
    }

public:
    bool invalid{false};
    IHttpStatusCode status{IHttpStatus::UNKNOWN};
    QString name;
    QString description;
};

template<typename T>
class IHttpInvalidInterface : public IHttpInvalidWare
{
public:
    IHttpInvalidInterface(IHttpStatusCode code, const QString& description="");
};

template<typename T>
IHttpInvalidInterface<T>::IHttpInvalidInterface(IHttpStatusCode status, const QString& description)
    : IHttpInvalidWare(status, IMetaUtil::getBareTypeName<T>(), description)
{
}

$PackageWebCoreEnd

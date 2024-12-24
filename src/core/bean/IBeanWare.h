#pragma once

#include "core/util/IPackageUtil.h"

$PackageWebCoreBegin

class IBeanWare
{
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;

public:
    virtual IJson toJson() const = 0;
    virtual bool loadJson(const IJson&) = 0;

public: // TODO:
    virtual QVariant getFieldValue(const QString& name) const {return {};}
    virtual void setFieldValue(const QString& name, const QVariant& value) {}
};

$PackageWebCoreEnd

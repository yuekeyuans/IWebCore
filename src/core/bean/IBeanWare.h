#pragma once

#include <QString>
#include <QVariant>
#include "core/util/IPackageUtil.h"

$PackageWebCoreBegin

// TODO: 考虑删掉这个东西
class IBeanWare
{
public:
    IBeanWare() = default;
    virtual ~IBeanWare() = default;

public:
    virtual QVariant getFieldValue(const QString& name) const = 0;
    virtual void setFieldValue(const QString& name, const QVariant& value) = 0;
};

$PackageWebCoreEnd

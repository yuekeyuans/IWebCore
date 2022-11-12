#pragma once

#include "base/IHeaderUtil.h"
#include "base/IMetaUtil.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "web/jar/IJarUnit.h"
#include "web/net/IMultiPart.h"

$PackageWebCoreBegin

class IMultiPartJar : public IJarUnit, IRegisterMetaTypeUnit<IMultiPartJar>
{
    Q_GADGET
    $UseMetaRegistration(IMultiPartJar)
public:
    using IJarUnit::IJarUnit;

public:
    IMultiPartJar();
    const IMultiPart &operator[](const QString& name) const;

    bool containRequestMulitPartName(const QString& name) const;
    QStringList getRequestMultiPartNames() const;

    const IMultiPart& getRequestMultiPart(const QString& name, bool* ok=nullptr) const;

    const QVector<IMultiPart>& getRequestMultiParts() const;
    QVector<IMultiPart> getRequestFileMultiParts() const;
};

$PackageWebCoreEnd

#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/result/IResult.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/jar/IJarUnit.h"
#include "http/jar/IMultiPart.h"

$PackageWebCoreBegin

class IMultiPartJar : public IJarUnit, IRegisterMetaTypeUnit<IMultiPartJar>
{
public:
    using IJarUnit::IJarUnit;

public:
    IMultiPartJar();
    IMultiPart operator[](IStringView name) const;
    IMultiPart operator[](const QString& name) const;

    bool containRequestMulitPartName(IStringView name) const;
    bool containRequestMulitPartName(const QString& name) const;
    QStringList getRequestMultiPartNames() const;

    IMultiPart getRequestMultiPart(IStringView name) const;
    IMultiPart getRequestMultiPart(const QString& name) const;

    const QVector<IMultiPart>& getRequestMultiParts() const;
    QVector<IMultiPart> getRequestFileMultiParts() const;
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/base/IResult.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/IJarUnit.h"
#include "http/net/IMultiPart.h"

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
    IStringViewList getRequestMultiPartNames() const;

    IMultiPart getRequestMultiPart(IStringView name) const;
    IMultiPart getRequestMultiPart(const QString& name) const;

    const QVector<IMultiPart>& getRequestMultiParts() const;
    QVector<IMultiPart> getRequestFileMultiParts() const;
};

$PackageWebCoreEnd

#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/base/IResult.h"
#include "http/IJarUnit.h"
#include "http/IMultiPart.h"

$PackageWebCoreBegin

class IMultiPartJar : public IJarUnit
{
public:
    using IJarUnit::IJarUnit;

public:
    const IMultiPart& operator[](const IString& name) const;
    const IMultiPart& operator[](const QString& name) const;

    bool contain(const IString& name) const;
    bool contain(const QString& name) const;
    IStringViewList getNames() const;

    const IMultiPart& getMultiPart(const IString& name) const;
    const IMultiPart& getMultiPart(const QString& name) const;
    const std::vector<IMultiPart>& getRequestMultiParts() const;
};

$PackageWebCoreEnd

﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/base/IResult.h"
#include "core/unit/IRegisterMetaTypeUnit.h"
#include "http/net/IJarUnit.h"
#include "http/net/IMultiPart.h"

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
    IStringViewList getKeys() const;

    const IMultiPart& getMultiPart(const IString& name) const;
    const IMultiPart& getMultiPart(const QString& name) const;

    const QVector<IMultiPart>& getRequestMultiParts() const;
    QVector<IMultiPart> getRequestFileMultiParts() const;
};

$PackageWebCoreEnd

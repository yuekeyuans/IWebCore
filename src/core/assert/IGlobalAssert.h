#pragma once

#include "IAssertInterface.h"
#include "IAssertPreProcessor.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAssert : public IAssertInterface
{
    $AsAssert(IGlobalAssert)
public:
    IGlobalAssert() = default;

public:
    virtual void loadAssert() final;
};

$PackageWebCoreEnd

#include "IGlobalAssert.cpp"

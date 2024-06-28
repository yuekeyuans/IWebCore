#pragma once

#include "IAssertInterface.h"
#include "IAssertPreProcessor.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAssert1 : public IAssertInterface
{
    $AsAssert(IGlobalAssert1)
private:
    IGlobalAssert1() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd

#include "IGlobalAssert.cpp"

#pragma once

#include "IAssertInterface.h"
#include "IAssertPreProcessor.h"
#include "core/base/IHeaderUtil.h"

$PackageWebCoreBegin

class IGlobalAssert : public IAssertInterface
{
    $AsAssert(IGlobalAssert)
private:
    IGlobalAssert() = default;
    virtual void loadAssert() final;
};

$PackageWebCoreEnd

#include "IGlobalAssert.cpp"

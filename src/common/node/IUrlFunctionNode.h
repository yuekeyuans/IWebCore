#pragma once

#include "base/IHeaderUtil.h"
#include "common/biscuits/IHttpMethod.h"
#include "common/node/IFunctionNode.h"

$PackageWebCoreBegin

struct IUrlFunctionNode{
    void* parentNode{nullptr};
    bool  ignoreParamCheck{false};
    QString url;
    IHttpMethod httpMethod;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd

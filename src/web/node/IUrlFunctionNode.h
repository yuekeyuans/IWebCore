#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/node/IMethodNode.h"

$PackageWebCoreBegin

struct IUrlFunctionNode{
    void* parentNode{nullptr};
    bool  ignoreParamCheck{false};
    QString url;
    IHttpMethod httpMethod;

    IMethodNode functionNode;
};

$PackageWebCoreEnd

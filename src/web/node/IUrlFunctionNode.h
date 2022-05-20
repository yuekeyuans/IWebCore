#pragma once

#include "base/IHeaderUtil.h"
#include "web/biscuits/IHttpMethod.h"
#include "web/node/IFunctionNode.h"

$PackageWebCoreBegin

struct IUrlFunctionNode{
    void* parentNode{nullptr};
    bool  ignoreParamCheck{false};
    QString url;
    IHttpMethod httpMethod;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd

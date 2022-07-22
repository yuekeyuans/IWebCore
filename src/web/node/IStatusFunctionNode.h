#pragma once

#include "web/biscuits/IHttpStatus.h"
#include "web/node/IMethodNode.h"

$PackageWebCoreBegin

struct IStatusFunctionNode{
    IHttpStatus httpStatus;
    IMethodNode functionNode;
};

$PackageWebCoreEnd

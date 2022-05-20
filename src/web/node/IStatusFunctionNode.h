#pragma once

#include "web/biscuits/IHttpStatus.h"
#include "web/node/IFunctionNode.h"

$PackageWebCoreBegin

struct IStatusFunctionNode{
    IHttpStatus httpStatus;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd

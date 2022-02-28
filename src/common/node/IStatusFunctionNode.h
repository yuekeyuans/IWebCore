#pragma once

#include "biscuits/IHttpStatus.h"
#include "common/node/IFunctionNode.h"

$PackageWebCoreBegin

struct IStatusFunctionNode{
    IHttpStatus httpStatus;
    IFunctionNode functionNode;
};

$PackageWebCoreEnd

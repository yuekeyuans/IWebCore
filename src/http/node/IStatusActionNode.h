#pragma once

#include "http/biscuits/IHttpStatus.h"
#include "http/node/IMethodNode.h"

$PackageWebCoreBegin

struct IStatusActionNode{
    IHttpStatus httpStatus;
    IMethodNode methodNode;
};

$PackageWebCoreEnd
